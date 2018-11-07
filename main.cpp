#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>  // Get const chars size
#include <sstream>

static int fileTotalLength = 0;
static int filePartSize = 0;
static int currentFileNumber = 1;
static int filePartActual = 1;

std::vector<char> getFileData( const char *filePath)
{

    std::ifstream iFile;
    std::ifstream OFile;

    iFile.open(filePath);
    iFile.seekg(0, iFile.end);
    size_t  fileLength = iFile.tellg();

    iFile.seekg(0, iFile.beg);

    std::cout << "Tamanho do Arquivo " << fileLength;

    std::vector<char> buffer;

    if(fileLength > 0)
    {
        buffer.resize(fileLength);
        iFile.read(&buffer[0], fileLength);
    }

    return buffer;
}


static void splitFiles( const char *filePath , int numberParts)
{

    if(numberParts % 2 == 0 )
    std::cout << "Pair Parts" << std::endl;
    else
        numberParts++;

    std::ifstream iFile;
    std::ofstream OFile;

    iFile.open(filePath);
    iFile.seekg(0, iFile.end);

    fileTotalLength = iFile.tellg();
    filePartSize = fileTotalLength / numberParts;

    iFile.seekg(0, iFile.beg);

    std::cout << "Tamanho do Arquivo(Bytes): " << fileTotalLength << std::endl
              << "Part Size (Bytes): "<< filePartSize << std::endl;

    char *buffer;
    std::stringstream fileInfo;
    fileInfo << numberParts << std::endl;


    std::stringstream pathInfo;
    pathInfo << filePath;
    // Get file part extension
    for(int i = pathInfo.str().size(); i > 0; i -- )
    {
        if(filePath[i] == '.')
        {
            std::cout << "Dot founded in part of string : " << i << std::endl;
            int extensionSize = pathInfo.str().size() - i;

            std::cout << "Extension Name Size : " << extensionSize << std::endl;
            //pathInfo.clear();
            //pathInfo.str(std::string());
            //Clear string
            //char *test  = new char[extensionSize];
            std::stringstream extensionName ;

            for(int j = i ; j < pathInfo.str().size(); j ++ )
            {
               extensionName << filePath[j];
            }
            std::cout << "Extension Name" << extensionName.str() << std::endl;
            i = 0; // Break for ( @TODO: replace the for later with a while () )
            break;

        }
        // if( i = 0 )
        // {
        //     std::cout << "extension name not found" << std::endl;
        // }
    }
    std::cout << "Full Path "<< pathInfo.str() << std::endl;

    int PathSize = fileInfo.str().size();


    //size_t PathSize = std::strlen(filePath);



    OFile.open( "split/part0.part" , std::ios::binary );
    OFile.write( fileInfo.str().c_str(), PathSize );  // 4 for the maximum int file parts size possibler

    OFile.close();

    for(int i = 0 ; i < numberParts ; i++ )
    {
        std::string outputPartPath("split/split");
        std::ostringstream  output;
        output << i + 1;
        outputPartPath.append(output.str());
        outputPartPath.append(".part");

        std::cout << "Part File: " << outputPartPath <<  std::endl;

        //create file with open
        OFile.open( outputPartPath.c_str(), std::ofstream::binary );
        buffer =  new char[filePartSize];
        //iFile.seekg(filePartSize*2);
        iFile.read(buffer, filePartSize);

        if(fileTotalLength > 0)
        {
            const char *writeBuff = buffer;
            OFile.write(writeBuff, filePartSize);
        }

        OFile.close();

        delete buffer;

    }
}

static void joinFiles( )
{
    std::ifstream iFile;
    iFile.open("split/part0.part");

    iFile.seekg(0, iFile.end);
    int size = iFile.tellg();
    iFile.seekg(0, iFile.beg);

    char Buffer[size];
    int BufferValue;

    /*
    while(!iFile.eof())
    {
    }
    */

    iFile >> BufferValue;



    // Pegar numero total,.  encotnrar primeiro ponto e virgula subtrair total ;
    // Reler Array, e parar na posi;áo da primeira pono e v[irgula

    // for (int i = 0; i < size; ++i)
    // {
    //     Buffer[i] = ';' ? Buffer[i] == 0 : Buffer[i] == 0;
    // }

    std::cout << "Reading File Data : " << Buffer << std::endl;
    std::cout << " Test int " << BufferValue << std::endl;
    std::cout << " Test int " << BufferValue + 10 << std::endl;


}

int main(int argc, char *args[])
{

    // Se o endereço do arquivo estiver errado  haverá um erro de alocação de memória
    //std::vector<char> teste = getFileData("C:/Windows/explorer.exe");
    splitFiles( "C:/Users/marcos.toledo/Desktop/Projetos/SplitTest/arquivoTest.txt" ,  2 );

    joinFiles();

    return 0;
}
