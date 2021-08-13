#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>


int Index[12] = {68, 73, 76, 83, 88, 91, 68, 73, 75, 83, 88, 91};

int CharToNum(const char* line, int position);
int SpecialCharToNum(const char* line, int position);
bool CompareLines(const char* line1, const char* line2);
void SortLines(std::vector<std::string> &lines);
void PrintLines(const std::vector<std::string> &lines);
std::vector<std::string> GetLinesFromFile(std::string NameOfTheFile);
void PrintLinesToFile(const std::vector<std::string> &lines, std::string NameOfTheFile);
void CreateVCard(const std::vector<std::string> &lines, std::string NameOfTheFile);
bool LineHasSpecialCharacter(const std::string &line);
std::string ConvertFirstLine(const std::vector<std::string> &SplittedName, bool HasSpecialChar);
std::string ConvertSecondLine(const std::string &name, bool HasSpecialChar);
std::string WriteTelInfo(const std::string &telNumber);
std::string LinetoVCardHexString(const std::string &line);
std::string SpecialCharToHexString(const char* line, int position, bool &isSpecial);
std::string hex(int Number);
std::vector<std::string> split(std::string String, std::string splitstring);

int main()
{
    std::string InputFileName,SortedFileName,OutputFileName;
    std::cout << "Dosya ismini uzanti olmadan giriniz (Mesela dosya ismi Rehber.csv ise Rehber olarak giriniz):\n";
    std::cin >> InputFileName;
    SortedFileName = InputFileName + "_Alfabetik_SIRALI.csv";
    OutputFileName = InputFileName + ".vcf";
    InputFileName += ".csv";

    std::vector<std::string> lines;
    lines = GetLinesFromFile(InputFileName);
    SortLines(lines);
    PrintLinesToFile(lines, SortedFileName);
    CreateVCard(lines,OutputFileName);
}

int SpecialCharToNum(const char* line, int position)
{
    int Result = 0;
    int Index1 = 0;
    if (line[position] == -61 && line[position+1] == -121)
        Index1 = 1;
    else if (line[position] == -60 && line[position+1] == -98)
        Index1 = 2;
    else if (line[position] == -60 && line[position+1] == -80)
        Index1 = 3;
    else if (line[position] == -61 && line[position+1] == -106)
        Index1 = 4;
    else if (line[position] == -59 && line[position+1] == -98)
        Index1 = 5;
    else if (line[position] == -61 && line[position+1] == -100)
        Index1 = 6;
    else if (line[position] == -61 && line[position+1] == -89)
        Index1 = 7;
    else if (line[position] == -60 && line[position+1] == -97)
        Index1 = 8;
    else if (line[position] == -60 && line[position+1] == -79)
        Index1 = 9;
    else if (line[position] == -61 && line[position+1] == -74)
        Index1 = 10;
    else if (line[position] == -59 && line[position+1] == -97)
        Index1 = 11;
    else if (line[position] == -61 && line[position+1] == -68)
        Index1 = 12;
    else
        Index1 = 0;

    if (Index1)
    {
        Result = Index[Index1 - 1];
    }
    return Result;
}
int CharToNum(const char* line, int position)
{
    int Number;
    if (line[position] == 'i')
    {
        return 76;
    }
    Number = toupper(line[position]);
    if (Number > 67)
        Number++;
    if (Number > 72)
        Number++;
    if (Number > 75)
        Number++;
    if (Number > 82)
        Number ++;
    if (Number > 87)
        Number ++;
    if (Number > 90)
        Number ++;
    return Number;
}

bool CompareLines(const char* line1, const char* line2)
{
    int Number1;
    int Number2;
    int index1 = 0;
    int index2 = 0;
    size_t size1 = strlen(line1);
    size_t size2 = strlen(line2);
    
    while(line1[index1] != ',' && line2[index2] != ',')
    {
        // Converting Char To Number
        Number1 = SpecialCharToNum(line1,index1);
        Number2 = SpecialCharToNum(line2,index2);

        if(Number1) // If It is a Special Character
        {
            index1+=2;
        }
        else
        {
            Number1 = CharToNum(line1,index1);
            index1++;
        }

        if(Number2) // If It is a Special Character
        {
            index2+=2;
        }
        else
        {
            Number2 = CharToNum(line2,index2);
            index2++;
        }

        if(Number1 < Number2)
        {
            return false;
        }
        else if (Number1 > Number2)
        {
            return true;
        }
    }
    if (size1 < size2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void SortLines(std::vector<std::string> &lines)
{
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = i+1; j < lines.size();j++)
        {

            bool isPrev = CompareLines(lines[i].c_str(), lines[j].c_str());
            if(isPrev)
            {
                swap(lines[i],lines[j]);
            }
        }
    }
}
void PrintLines(const std::vector<std::string> &lines)
{
    for(auto line : lines)
    {
        std::cout << line << std::endl;
    }
}

std::vector<std::string> GetLinesFromFile(std::string NameOfTheFile)
{
    std::ifstream InputFile;
    std::vector<std::string> lines;
    std::string line;
    InputFile.open(NameOfTheFile);
    while(InputFile.is_open())
    {
        if(getline(InputFile,line))
        {
            lines.push_back(line);
        }
        else
        {
            InputFile.close();
        }
    }
    return lines;
}

void PrintLinesToFile(const std::vector<std::string> &lines, std::string NameOfTheFile)
{
    std::ofstream OutFile;
    OutFile.open(NameOfTheFile);

    if(OutFile.is_open())
    {
        for (auto line : lines)
        {
            OutFile << line << "\n";
        }
        OutFile.close();
    }
}
void CreateVCard(const std::vector<std::string> &lines, std::string NameOfTheFile)
{
    // Open the vcf file
    std::ofstream VcardFile;
    VcardFile.open(NameOfTheFile);

    if(VcardFile.is_open())
    {
        for (auto line : lines)
        {
            VcardFile << "BEGIN:VCARD\n";
            VcardFile << "VERSION:2.1\n";
            std::vector<std::string> SplittedLine = split(line,",");
            std::string PersonName = SplittedLine[0];
            std::string PersonNumber = SplittedLine[1];
            if(LineHasSpecialCharacter(line))
            {
                std::string NameInHexStream = LinetoVCardHexString(PersonName);
                std::vector<std::string> SplittedHexStream = split(NameInHexStream, "=20");
                VcardFile << ConvertFirstLine(SplittedHexStream,true) << "\n";
                VcardFile << ConvertSecondLine(NameInHexStream,true) << "\n";
            }
            else
            {
                std::vector<std::string> SplittedName = split(PersonName, " ");
                VcardFile << ConvertFirstLine(SplittedName,false) << "\n";
                VcardFile << ConvertSecondLine(PersonName,false) << "\n";
            }
            VcardFile << WriteTelInfo(PersonNumber) << "\n";
            VcardFile << "END:VCARD\n";
        }
        // close the vcf File
        VcardFile.close();
    }
}
bool LineHasSpecialCharacter(const std::string &line)
{
    bool bResult = false;
    int Number, index = 0;
    const char* lineCString = line.c_str();
    while(lineCString[index] != 0)
    {
        Number = SpecialCharToNum(lineCString,index);
        if(Number)
        {
            bResult = true;
            break;
        }
        else
        {
            index++;
        }
    }
    return bResult;
}
std::string LinetoVCardHexString(const std::string &line)
{
    bool isSpecial = false;
    std::string HexString = "";
    int index = 0;
    const char* lineCString = line.c_str();
    while(lineCString[index] != 0)
    {
        HexString += SpecialCharToHexString(lineCString,index,isSpecial);
        if(isSpecial)
        {
            index += 2;
        }
        else
        {
            HexString += "=" + hex(lineCString[index]);
            index++;
        }
    }
    return HexString;
}

std::string ConvertFirstLine(const std::vector<std::string> &SplittedName, bool HasSpecialChar)
{
    std::string convertedLine = "N";
    if (HasSpecialChar)
    {
        convertedLine += ";CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:";
    }
    else
    {
        convertedLine += ":";
    }

    if(SplittedName.size() == 1)
    {
        convertedLine += ";";
        convertedLine += SplittedName[0];
        convertedLine += ";;;";
    }
    else if(SplittedName.size() == 2)
    {
        convertedLine += SplittedName[SplittedName.size()-1];
        convertedLine += ";";
        convertedLine += SplittedName[0];
        convertedLine += ";;;";
    }
    else if(SplittedName.size() == 3)
    {
        convertedLine += SplittedName[SplittedName.size()-1];
        convertedLine += ";";
        convertedLine += SplittedName[0];
        convertedLine += ";";
        convertedLine += SplittedName[1];
        convertedLine += ";;";
    }
    else
    {
        convertedLine += SplittedName[SplittedName.size()-1];
        convertedLine += ";";
        for(int i = 0; i < SplittedName.size()-2; i++)
        {
            convertedLine += SplittedName[i] + " ";
        }
        convertedLine += SplittedName[SplittedName.size()-2];
        convertedLine += ";;";
    }
    return convertedLine;
}
std::string ConvertSecondLine(const std::string &name, bool HasSpecialChar)
{
    std::string convertedLine = "FN";
    if(HasSpecialChar)
    {
        convertedLine += ";CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:";
    }
    else
    {
        convertedLine += ":";
    }
    convertedLine += name;
    return convertedLine;
}
std::string WriteTelInfo(const std::string &telNumber)
{
    std::string result = "TEL;CELL:";
    result += telNumber;
    return result;
}

std::string hex(int Number)
{
    std::stringstream sstream;
    sstream << std::hex << Number;
    std::string result = sstream.str();
    std::transform(result.begin(), result.end(),result.begin(), ::toupper);
    return result;
}

std::string SpecialCharToHexString(const char* line, int position, bool &isSpecial)
{
    isSpecial = false;
    std::string HexString = "";
    int Index1 = 0;
    if (line[position] == -61 && line[position + 1] == -121)
        Index1 = 1;
    else if (line[position] == -60 && line[position + 1] == -98)
        Index1 = 2;
    else if (line[position] == -60 && line[position + 1] == -80)
        Index1 = 3;
    else if (line[position] == -61 && line[position + 1] == -106)
        Index1 = 4;
    else if (line[position] == -59 && line[position + 1] == -98)
        Index1 = 5;
    else if (line[position] == -61 && line[position + 1] == -100)
        Index1 = 6;
    else if (line[position] == -61 && line[position + 1] == -89)
        Index1 = 7;
    else if (line[position] == -60 && line[position + 1] == -97)
        Index1 = 8;
    else if (line[position] == -60 && line[position + 1] == -79)
        Index1 = 9;
    else if (line[position] == -61 && line[position + 1] == -74)
        Index1 = 10;
    else if (line[position] == -59 && line[position + 1] == -97)
        Index1 = 11;
    else if (line[position] == -61 && line[position + 1] == -68)
        Index1 = 12;
    else
        Index1 = 0;

    if (Index1)
    {
        unsigned char char1 = (unsigned char)line[position];
        unsigned char char2 = (unsigned char)line[position + 1];
        HexString += "=" + hex(char1) + "=" + hex(char2);
        isSpecial = true;
    }
    return HexString;
}

std::vector<std::string> split(std::string String, std::string splitstring)
{
    std::vector<std::string> SplittedVector;
    size_t found = String.find(splitstring);
    while (found != std::string::npos)
    {
        if (found != 0)
        {
            SplittedVector.push_back(String.substr(0,found));
            String = String.substr(found + splitstring.size(),String.size()-(found+splitstring.size()));
        }
        found = String.find(splitstring);
    }
    SplittedVector.push_back(String.substr(0,String.size()));
    return SplittedVector;
}