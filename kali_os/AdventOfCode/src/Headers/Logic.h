#include <bits/stdc++.h>
using namespace std;

class Logic{
    private:
        int problemNumber;
        string inputFileLocation;
        string outputFileLocation;

        void Logic_01();
        void Logic_02();
        void Logic_03();
        void Logic_04();
        void Logic_05();
        void Logic_11();
        void Logic_12();
        void Logic_13();
        void Logic_14();
        void Logic_15();
        void Logic_16();
    public: 
        Logic(int problemNumberInput)
        {
            problemNumber = problemNumberInput;
            inputFileLocation = ("/files/input_" + to_string(problemNumber) + ".txt");
            outputFileLocation = ("/files/output_" + to_string(problemNumber) + ".txt");
            // freopen("files/input_1.txt", "r", stdin);
            // freopen("files/output_1.txt", "w", stdout);
        }
        void Run()
        {
            switch(problemNumber){
                case 1: 
                    Logic_01();
                    break;
                case 2:
                    Logic_02();
                    break;
                case 3:
                    Logic_03();
                    break;
                case 4:
                    Logic_04();
                    break;
                case 5:
                    Logic_05();
                    break;
                case 11:
                    Logic_11();
                    break;
                case 12:
                    Logic_12();
                    break;
                case 13:
                    Logic_13();
                    break;
                case 14:
                    Logic_14();
                    break;
                case 15:
                    Logic_15();
                    break;
                case 16:
                    Logic_16();
                    break;
                default:
                    cout<<"Problem Number "<<problemNumber<<" is not Solved Yet\n";
                    break;
            }

        }
        ~Logic()
        {
            fclose(stdin);
            fclose(stdout);
        }
};
