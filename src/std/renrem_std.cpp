/************************************************************************
renrem: An acronym for [rename] and [remove] file, based on             *
        regular expressions which uses: ECMAScript 262.                 *
                                                                        *
Copyright (C) 2017  Shakib ( k-five )                                   *
                                                                        *
This program is free software: you can redistribute it and/or modify    *
it under the terms of the GNU General Public License as published by    *
the Free Software Foundation, either version 3 of the License, or       *
(at your option) any later version.                                     *
                                                                        *
This program is distributed in the hope that it will be useful,         *
but WITHOUT ANY WARRANTY; without even the implied warranty of          *
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
GNU General Public License for more details.                            *
                                                                        *
You should have received a copy of the GNU General Public License       *
along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
                                                                        *
*************************************************************************
                this version uses std::regex library
************************************************************************/
#define GCC_VERSION ( __GNUC__ * 100 + __GNUC_MINOR__ * 10  + __GNUC_PATCHLEVEL__ )
#if GCC_VERSION >= 540   // 540 == 5.4.0
    #include <regex>
    #include <string>
    #include <sstream>
///////////////////
    #include <cstdio>
///////////////////
#else
    #error you need to use gcc version 5.4.0 or upper, since the lower version of gcc has some bugs in regex library
#endif // GCC_VERSION

#define green_color std::string( "\033[1;32m" )
#define red_color   std::string( "\033[1;31m" )
#define reset_color std::string( "\033[m" )

#define red_color_match "\033[1;31m$&\033[m"
#define prefix_and_match  "$`$&"

#define __RENREM_VERSION__ "0.3.4"

void get_help( const char* what = "get_help() was called" );

int main( int argc,const char** const argv ){

    if( argc < 2 ){
        get_help( "ERROR: missing the first argument" );
        return 0;
    }

    /***************************************************/
    /* checking if the user entered correct synopsis   */
    /***************************************************/

    std::string argv_1 = argv[ 1 ];
    bool rename_is_correct = std::regex_match( argv_1, std::regex( "s?([/|@#])(?:(?!\\1).)+\\1(?:(?!\\1).)*\\1(?:(?:gi?|ig)?(?:\\1-?[1-9]\\d?)?|i)?" ) );
    bool remove_is_correct = std::regex_match( argv_1, std::regex( "d?([/|@#])(?:(?!\\1).)+\\1(?:gi?|ig?)?" ) );

    if      ( rename_is_correct && !remove_is_correct ) {}
    else if ( !rename_is_correct && remove_is_correct ) {}
    else    { get_help( "ERROR: bad input syntax" ); return 0; }

    /*************************************/
    /* setting up the auto zeros-leading */
    /*************************************/

    const char** clone_argv = argv + 2; // argv + 2: for skipping the name of the program and the first argument
    char str_argc       [ 10 ]{};
    char rename_format  [ 50 ]{};
    char remove_format  [ 30 ]{};

    sprintf( str_argc, "%d", argc - 2 );    // argc - 2: for ignore the name of the program and the first argument
    sprintf( rename_format, "%%0%dd rename: %%s \033[1;36m>>\033[m %%s", std::string( str_argc ).size() );
    sprintf( remove_format, "%%0%dd remove: %%s", std::string( str_argc ).size() );

    /****************************************************/
    /* extracting the user-entered input into variables */
    /****************************************************/

    char action_flag = '\0';
    char delimiter   = '\0';

    short number_of_delimiter = 0;

    std::string match;
    std::string substitute;

    char end_flag[ 3 ]{ '\0', '\0', '\0' };

    int index       = 0;
    int clone_index = 0;

    std::istringstream iss( argv_1 );

    if( iss.peek() == 's' || iss.peek() == 'd' ){

        action_flag = iss.get();    // extracts 's' or 'd'
        delimiter   = iss.get();    // extracts delimiter

        for( const char ch : argv_1 ) if( ch == delimiter ) ++number_of_delimiter;

        std::getline( iss, match, delimiter );
        std::getline( iss, substitute, delimiter );

        iss.get( end_flag, sizeof( end_flag ) / sizeof( char ), delimiter );
        iss.get();  // get rid of delimiter
        iss >> index;
        clone_index = index;

    } else {

        delimiter = iss.get();  // extracts delimiter

        for( const char ch : argv_1 ) if( ch == delimiter ) ++number_of_delimiter;

        std::getline( iss, match, delimiter );

        if( number_of_delimiter >= 3 ){
            std::getline( iss, substitute, delimiter );
            iss.getline( end_flag, sizeof( end_flag ) / sizeof( char ), delimiter );
        } else {
            iss.get( end_flag, sizeof( end_flag ) / sizeof( char ), delimiter );
        }

        iss >> index;
        clone_index = index;
    }

    /********************************************************/
    /* checking for throwing any exceptions from std::regex */
    /********************************************************/

    try{
        std::regex regex ( match );
    } catch( const std::regex_error& re ){
        printf( "%s: %s\n", "input regex error", re.what() );
        return 0;
    }

    /********************************************/
    /* initializing the regex and related flags */
    /********************************************/

    std::regex::flag_type regex_flag = std::regex_constants::ECMAScript;
    for( const char chr : end_flag ){
        if( chr == 'i' )
            regex_flag = std::regex_constants::icase;
    }
    std::regex regex( match, regex_flag );

    std::regex_constants::match_flag_type search_flag = std::regex_constants::format_first_only;
    for( const char chr : end_flag ){
        if( chr == 'g' )
            search_flag = std::regex_constants::match_default;
    }
    std::smatch match_result;

    std::string old_name;
    std::string old_name_colorize;
    std::string new_name;
    std::string new_name_colorize;

    std::string dir_name;

    /*******************/
    /* while loop over */
    /* all lists that  */
    /* was passed to   */
    /* the program     */
    /*******************/

    std::size_t counter = 0;

    while( *clone_argv ){

        dir_name = *clone_argv;

            if( std::regex_search( dir_name, match_result, regex ) ){

                old_name          = dir_name;
                old_name_colorize = std::regex_replace( dir_name, regex, red_color_match , search_flag );   // red_color_match uses match_result above

                /*********************************************************/
                /* finding the number of match to fix the negative index */
                /*********************************************************/

                if( index ){

                    if( index < 0 ){    // for fixing the negative index
                        ++index;        // add 1 to fix the size

                        while( std::regex_search( dir_name, match_result, regex ) ){
                            dir_name = match_result.suffix();
                            ++index;    // counts the number of match
                        }

                        dir_name = *clone_argv; // update dir_name
                    }

                    /********************************************************/
                    /* finding the correct index of the match to substitute */
                    /********************************************************/

                    while( std::regex_search( dir_name, match_result, regex ) ){

                        if( ! --index ){
                            new_name_colorize += std::regex_replace( dir_name, regex, green_color + substitute + reset_color, std::regex_constants::format_first_only );
                            new_name          += std::regex_replace( dir_name, regex, substitute, std::regex_constants::format_first_only );
                            break;            // after finding the user apply for index
                        }
                        new_name          += match_result.format( prefix_and_match );
                        new_name_colorize += match_result.format( prefix_and_match );

                        dir_name = match_result.suffix();
                    }


                } else {                                  // so there is not index then:
                    new_name          = std::regex_replace( dir_name, regex, substitute, search_flag );
                    new_name_colorize = std::regex_replace( dir_name, regex, green_color + substitute + reset_color, search_flag );
                }

                if( number_of_delimiter >= 3 ){
                    if ( index ){                         // if index != 0; it means out_of_range has occurred!
                        new_name          += dir_name;    // just for fixing the end of the string( for last match_result.suffix() ) like: t + emp
                        new_name_colorize += dir_name;    // just for fixing the end of the string( for last match_result.suffix() ) like: t + emp
                    }
                    printf( rename_format, ++counter, old_name_colorize.c_str(), new_name_colorize.c_str() );

                    /**********************************/
                    /* rename if the 's' flag was set */
                    /**********************************/
                    if( ( action_flag == 's' ) && ( new_name != old_name ) ){
                        const short result = rename( old_name.c_str(), new_name.c_str() );
                        if( result == 0 ){
                            printf( " [Success]\n" );               // for 0 it says: Success
                        } else {
                            printf( " [%s]\n", strerror( errno ) ); // for non-zero it says the appropriate error, like: Operation not permitted
                        }
                    } else {
                        puts( "" );                                 // just prints newline
                    }

                } else {
                    printf( remove_format, ++counter, old_name_colorize.c_str() );

                    /*********************************/
                    /* remove if the 'd' flag is set */
                    /*********************************/

                    if( action_flag == 'd' ){
                        const short result = remove( old_name.c_str() );
                        if( result == 0 ){
                            printf( " [Success]\n" );               // for 0 it says: Success
                        } else {
                            printf( " [%s]\n", strerror( errno ) ); // for non-zero it says the appropriate error, like: Operation not permitted
                        }
                    } else {
                        puts( "" );                                 // just prints newline
                    }
                }
            }

        ++clone_argv;

        new_name.clear();
        new_name_colorize.clear();
        index = clone_index;
    }

    /*******************/
    /* end of the code */
    /*******************/

return 0; }

void get_help( const char* what ){
const char* usage =
R"(Usage:
    rename:     /match/substitute/
                /match/substitute/g     ( global )
                /match/substitute/i     ( case-sensitive )
                /match/substitute/gi    ( both )
                /match/substitute/gi/5  ( 5th match from the beginning )
                /match/substitute/gi/-1 ( 1th match from the end = last match )

    remove:     /match/
                /match/g                ( global )
                /match/i                ( case-sensitive )
                /match/gi               ( both )


Note:
    start flag can only be:   s or d
    delimiter can only be:    / or | or # or @
    end flag can only be:     g or i
    index match is only accepted after 'g' flag

    You should use single quote ( ' ) or may double quote ( " )
    and it depends on your machine.

    Without 's' flag and 'd' flag the program just prints to the
    screen and does not do anything.

Examples:
    Print to the screen plus doing:
    rename:
    renrem 's/\d/_/g/3'  ( = globally, match all digits, but only substitute the 3th digit )
    renrem 's/\d/_/g/-1' ( = globally, match all digits, but only substitute the last digit )

    remove:
    renrem 'd/\d/g'      ( = globally, match all digits and remove those files )

renrem: An acronym for [rename] and [remove] file, based on
        regular expressions which uses: ECMAScript 262.

Copyright (C) 2017  Shakib
source and bug report: github.com/k-five/renrem)";
    printf( "%s\n", usage );
    printf( "%s: %s\n\n", "version", __RENREM_VERSION__ );
    printf( "%s\n", what );
}
