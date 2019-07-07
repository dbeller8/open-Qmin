#include "fileGenerator.h"
#include <iomanip>
#include <fstream>
#include <sstream>

/*! \file fileGenerator.cpp */

void fileGenerator::initialize()
    {
    cout << "initializing customScriptFromGUI.cpp"<< endl;
    lines.clear();
    string dir=DIRECTORY;
    string outName="/customScriptFromGUI.cpp";
    outputName = dir+outName;

    //the constructor first copies the front matter of the main openQmin file
    string inName=dir+"/openQmin.cpp";
    string line;
    ifstream infile(inName);
    for (int ll = 0; ll < 150; ++ll)
        {
        getline(infile,line);
        if(ll != 139 && ll != 138 && ll != 150)
            {
            addLine(line);
            };
        };

        addLine("\tshared_ptr<energyMinimizerFIRE> fire;");
        addLine("\tshared_ptr<energyMinimizerNesterovAG> nesterov;");

        addLine("\tscalar globalLx = boxLx*rankTopology.x;");
        addLine("\tscalar globalLy = boxLy*rankTopology.y;");
        addLine("\tscalar globalLz = boxLz*rankTopology.z;");
    };

void fileGenerator::save()
    {
    char fn[256];
    sprintf(fn,"%s",outputName.c_str());
    cout << "saving a file of length " << lines.size() <<" to " <<outputName << endl;
    ofstream myfile;
    myfile.open(fn);
    for (int ii = 0; ii < lines.size(); ++ii)
        {
        myfile << lines[ii];
        }
    myfile << "\n\n\n\tMPI_Finalize();\n\treturn 0;\n\t};\n";
    myfile.close();
};
