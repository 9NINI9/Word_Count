#include <iostream>
using namespace std;
int lines_count (string Name_files){
    FILE *fp = fopen(Name_files.c_str(), "r");
    char symbol_i;
    int lines_count = 0;
    while((symbol_i = (char)getc(fp)) != EOF){
        if (symbol_i == '\n') lines_count++;
    }
    if(lines_count == 0){
        fseek(fp, 0, SEEK_SET);
        if(getc(fp) != EOF){
            cout <<  "number of lines: 1" << endl;
            return 0;
        }
    }
    fseek(fp, -1, SEEK_END);
    if(getc(fp) == '\n') lines_count++;
    fclose(fp);
    if(lines_count >= 1) lines_count++;
    cout << "number of lines: " << lines_count << endl;
}
int words_count (string Name_files){
    FILE *fp = fopen(Name_files.c_str(), "r");
    char symbol_i;
    int words_count = 0;
    bool flag_words_in_file = false;
    while((symbol_i = (char)getc(fp)) != EOF){
        if(!flag_words_in_file && (symbol_i != '\n' || symbol_i != ' ' || symbol_i != '\t')){
            words_count++;
            flag_words_in_file = true;
        }
        else {
            if (flag_words_in_file && (symbol_i == '\n' || symbol_i == ' ' || symbol_i == '\t')) {
                flag_words_in_file = false;
            }
        }
        cout << endl;
    }
    fclose(fp);
    cout << "word count: " << words_count << endl;
}
int bytes_count (string Name_files){
    FILE *fp = fopen(Name_files.c_str(), "r");
    fseek(fp, 0, SEEK_END);
    int bytes_count = ftell(fp);
    fclose(fp);
    cout << "number of bytes: " << bytes_count << endl;
}
int main(int argc, char** argv) {
    int flag_lines = 0, flag_bytes = 0, flag_words = 0;
    string Name_files = "empty";
    for(int i = 1; i < argc; i++){
        if(argv[i][0] != '-') Name_files = argv[i];
    }
    if(argc == 1) cout << "Only the name of the program is entered" << endl;
    if(Name_files == "empty") {
        cout << "File path not specified in console";
        return 0;
    }
    if(argc == 2){
        Name_files = argv[1];
        lines_count(Name_files);
        words_count(Name_files);
        bytes_count(Name_files);
    }
    else{
        for(int i = 1; i < argc; i++){
            string Arguments;
            Arguments = argv[i];
            if(Arguments[0] == '-' && Arguments[1] != '-'){
                for(int j = 1; j < Arguments.length(); j++){
                    if(Arguments[j] == 'l' && flag_lines != 1){
                        lines_count(Name_files);
                        flag_lines++;
                    }
                    if(Arguments[j] == 'w' && flag_words != 1){
                        words_count(Name_files);
                        flag_words++;
                    }
                    if(Arguments[j] == 'b' && flag_bytes != 1){
                        bytes_count(Name_files);
                        flag_bytes++;
                    }
                }
            }
            if(Arguments[0] == '-' && Arguments[1] == '1'){
                if(Arguments == "--lines" && flag_lines != 1){
                    lines_count(Name_files);
                    flag_lines++;
                }
                if(Arguments == "--words" && flag_words != 1){
                    words_count(Name_files);
                    flag_words++;
                }
                if(Arguments == "--bytes" && flag_bytes != 1){
                    bytes_count(Name_files);
                    flag_bytes++;
                }
            }
        }
    }
    return 0;
}
