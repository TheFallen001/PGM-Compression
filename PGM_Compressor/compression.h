#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <iostream>
#include <fstream>


using namespace std;

/**
 * @brief A class that takes the attributres of the pgm file
 */
class Compression
{
private:
    string magic_num;
    int height;
    int width;
    int max_pixel_num;

public:
    /**
     * @brief a Constructor
     */
    Compression(string magic_num, int height, int width, int max_pixel_num);

    /**
     * @brief Getter function for magic number.
     * @return String
     * */
    string getMagicNum();

    /**
     * @brief Getter function for height.
     * @return Integer
     */
    int getHeight();

    /**
     * @brief Getter function for width.
     * @return Integer
     */
    int getWidth();

    /**
     * @brief Getter function for maximum pixel number.
     * @return Integer
     */
    int getMaxPixelNum();

    /**
     * @brief A function that checks if the file is P5 or P2.
     * @return Boolean
     */
    bool P2Check();

    /**
     * @brief A function that converts decimal numbers to hexadecimal.
     * @param param1 Integer number to be converted.
     * @return String number in hexadecimal.
     */
    string decToHexa(int n);

    /**
     * @brief A function that compresses P2 pgm files.
     * @param param1 Streampos. this gets the position to place the read pointer on the input file.
     * @param param2 String. this is the name of the file to be read from.
     * @param param3 String. this is the name of the file to be written to.
     */
    void P2Compress(streampos pos, string input_file, string output_file);

    /**
     * @brief A function that decompresses P2 pgm files
     * @param param1 String. this is the name if the file to be read from.
     * @param param2 String. this is the name of the file to be written to.
     * @param param3 Streampos. this places the position of the read pointer in the file
     */
    void P2Decompress(string input_file, string output_file, streampos pos);

    
};
/**
 * @brief A function that writes the information of the PGM file to the specified file.
 * @param param1 Compression. this is a class that holds the information of the PGM file.
 * @param param2 String. this is the name of the file to written to.
 * @param param3 Streampos reference. gets the position of the writing pointer.
 */
void writeInfo(Compression image, string output_file, streampos &pos);

/**
 * @brief A function that reads the information of the PGM file to a Compression object.
 * @param param1 String. this is the name of the file to read from.
 * @param param2 Streampos pointer. this gets the last read position of file.
 * @return Compression. this returns a Compression object.
 */
Compression readInfo(string input_file, streampos &pos);

Compression::Compression(string magic_num, int height, int width, int max_pixel_num)
{
    this->magic_num = magic_num;
    this->height = height;
    this->width = width;
    this->max_pixel_num = max_pixel_num;
}

string Compression::getMagicNum()
{
    return this->magic_num;
}

int Compression::getWidth()
{
    return this->width;
}

int Compression::getHeight()
{
    return this->height;
}

int Compression::getMaxPixelNum()
{
    return this->max_pixel_num;
}

bool Compression::P2Check()
{
    if ((this->getMagicNum()) == "P2")
    {
        return true;
    }

    return false;
}

Compression readInfo(string input_file, streampos &pos)
{
    ifstream handler(input_file);

    string magic_num;
    int height, width, max_pixel_num;

    handler >> magic_num;
    handler >> width;
    handler >> height;
    handler >> max_pixel_num;

    pos = handler.tellg();

    Compression image(magic_num, height, width, max_pixel_num);
    handler.close();
    return image;
}

void writeInfo(Compression image, string output_file, streampos &pos)
{
    ofstream handler(output_file);
    handler << image.getMagicNum() << ' ';
    handler << image.getWidth() << ' ';
    handler << image.getHeight() << ' ';
    handler << image.getMaxPixelNum() << ' ';
    cout << "Finished writing information" << endl;
    pos = handler.tellp();
    handler.close();
}

string Compression::decToHexa(int n)
{
    string answer = "";

    while (n != 0)
    {
        int rem = 0;
        char character;

        rem = n % 16;
        if (rem < 10)
        {
            character = rem + 48;
        }
        else
        {
            character = rem + 55;
        }

        answer += character;
        n /= 16;
    }

    int i = 0, j = answer.length() - 1;
    while (i < j)
    {
        swap(answer[i], answer[j]);

        i++;
        j--;
    }

    return answer;
}

void Compression::P2Compress(streampos pos, string input_file, string output_file)
{

    int temp;
    string answer;
    ifstream handler_in(input_file);
    ofstream handler_out(output_file, ios::app);

    handler_in.seekg(pos);

    while (handler_in >> temp)
    {
        if (temp == 0)
        {
            answer = "00";
        }
        else if (temp > 0 && temp <= 15)
        {
            answer = '0' + decToHexa(temp);
        }
        else
        {
            answer = decToHexa(temp);
        }
        handler_out << answer;
    }
    cout << "Compression complete" << endl;
    handler_in.close();
    handler_out.close();
}

void Compression::P2Decompress(string input_file, string output_file, streampos pos)
{
    ifstream handler_in(input_file);
    ofstream handler_out(output_file, ios::app);

    handler_in.seekg(pos);
    char *arr = new char[3];

    while (handler_in.read(arr, 2))
    {
        string temp;
        for (int i = 0; i < 3; i++)
        {
            temp += arr[i];
        }
        if (temp.size() == 1)
        {
            cout << "error" << endl;
        }

        int answer = stoi(temp, 0, 16);
        // HexaToDec(temp);

        handler_out << answer << ' ';
    }

    cout << "Decompression complete" << endl;
    delete[] arr;
    handler_in.close();
    handler_out.close();
}



#endif