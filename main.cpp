#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string read_file_contents(const string& filename);

bool match(const string& input, size_t& index, char expected) {
    if (index + 1 < input.length() && input[index + 1] == expected) {
        index++;
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    cout << unitbuf;
    cerr << unitbuf;    

    if (argc < 3) {
        cerr << "Usage: ./your_program tokenize <filename>" << endl;
        return 1;
    }

    const string command = argv[1];

    if (command == "tokenize") {
        string file_contents = read_file_contents(argv[2]);
        int line = 1;
        bool has_error = false;

        for (size_t i = 0; i < file_contents.length(); i++) {
            char c = file_contents[i];

            switch (c) {
                case '(':
                    cout << "LEFT_PAREN ( null" << endl; break;
                case ')':
                    cout << "RIGHT_PAREN ) null" << endl; break;
                case '{':
                    cout << "LEFT_BRACE { null" << endl; break;
                case '}':
                    cout << "RIGHT_BRACE } null" << endl; break;
                case ',':
                    cout << "COMMA , null" << endl; break;
                case '.':
                    cout << "DOT . null" << endl; break;
                case '-':
                    cout << "MINUS - null" << endl; break;
                case '+':
                    cout << "PLUS + null" << endl; break;
                case ';':
                    cout << "SEMICOLON ; null" << endl; break;
                case '*':
                    cout << "STAR * null" << endl; break;
                case '!':
                    cout << (match(file_contents, i, '=') ? "BANG_EQUAL != null" : "BANG ! null") << endl;
                    break;
                case '=':
                    cout << (match(file_contents, i, '=') ? "EQUAL_EQUAL == null" : "EQUAL = null") << endl;
                    break;
                case '<':
                    cout << (match(file_contents, i, '=') ? "LESS_EQUAL <= null" : "LESS < null") << endl;
                    break;
                case '>':
                    cout << (match(file_contents, i, '=') ? "GREATER_EQUAL >= null" : "GREATER > null") << endl;
                    break;
                case '/':
                    if (match(file_contents, i, '/')) {  
                        while (i + 1 < file_contents.length() && file_contents[i + 1] != '\n') i++;
                    } else if (match(file_contents, i, '*')) {  
                        while (i + 1 < file_contents.length()) {
                            if (file_contents[i] == '*' && i + 1 < file_contents.length() && file_contents[i + 1] == '/') {
                                i++;
                                break;
                            }
                            if (file_contents[i] == '\n') line++;
                            i++;
                        }
                    } else {  
                        cout << "SLASH / null" << endl;
                    }
                    break;
                case '\n':
                    line++;
                    break;
                default:
                    cerr << "[line " << line << "] Error: Unexpected character: " << c << endl;
                    has_error = true;
            }
        }

        cout << "EOF  null" << endl;
        
        if (has_error) {
            return 65;
        }

    } else {
        cerr << "Unknown command: " << command << endl;
        return 1;
    }

    return 0;
}

string read_file_contents(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error reading file: " << filename << endl;
        exit(1);
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
