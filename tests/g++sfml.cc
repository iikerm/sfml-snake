#include<iostream>
#include<vector>
#include<string>
using namespace std;


const string SYSLIB = "-lsfml-system";
const string WINLIB = "-lsfml-window";
const string GRALIB = "-lsfml-graphics";
const string NETLIB = "-lsfml-network";
const string AUDLIB = "-lsfml-audio";
const string OGLLIB = "-lGL";



int main(int argc, char *argv[]){
    bool hasN=false, hasO=false, fileFlagIteration=false;
    string fName, outName;

    string libsString;

    if (argc > 1){      // Must have system, window, graphics, network and audio libraries, as well as -n for name and -o for output name
        for (int i=1; i<argc; i++){
            if (argv[i] == (string)"-sys"){
                libsString += " " + SYSLIB;
            }else{
                if (argv[i] == (string)"-win"){
                    libsString += " " + WINLIB;
                }else{
                    if (argv[i] == (string)"-gra"){
                        libsString += " " + GRALIB;
                    }else{
                        if (argv[i] == (string)"-net"){
                            libsString += " " + NETLIB;
                        }else{
                            if (argv[i] == (string)"-aud"){
                                libsString += " " + AUDLIB;
                            }else{
                                if (argv[i] == (string)"-opengl"){
                                    libsString += " " + OGLLIB;
                                }else{
                                    if (argv[i] == (string)"-n"){
                                        if (argc > (i+1)){
                                            hasN = true;
                                            fName = argv[i+1];
                                            fileFlagIteration = true;
                                        }else{
                                            cout << "Invalid file name" << endl;
                                            return 1;
                                        }
                                    }else{
                                        if (argv[i] == (string)"-o"){
                                            if (argc > (i+1)){
                                                hasO = true;
                                                outName = argv[i+1];
                                                fileFlagIteration = true;
                                            }else{
                                                cout << "Invalid file name" << endl;
                                                outName = "compiled-sfml";
                                            }
                                        }else{
                                            if (fileFlagIteration){
                                                fileFlagIteration = false;
                                            }else{
                                                cout << "Invalid flag for program: " << argv[i] << endl;
                                                return 1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } 
            }
        }

        libsString = "g++ " + fName + " -o " + outName + " " + libsString;
        cout << libsString << endl;
        system((const char *)(libsString.c_str()));
    }

    return 0;
}