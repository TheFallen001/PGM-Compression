#include <iostream>
#include "compression.h"

using namespace std;

int main()
{
    char choice;
    cout << "__________________COMPRESSOR SOFTWARE__________________\n";
    cout << "Welcome.\n";
    cout << "Please pick one of the options below:\n";
    cout << "1. Compression.\n";
    cout << "2. Decompression\n";
    cin >> choice;

    string compress_file, output_file, compressed;
    while (1)
    {
        if (choice == '1')
        {

            cout << "Please enter the full path of the file you want to compress below:\n";
            cin >> compress_file;

            streampos read_pos, write_pos;
            Compression image = readInfo(compress_file, read_pos);
            if (image.P2Check())
            {
                cout << "\nWhat do you want the compressed image to be? \nWrite the name down below:\n";
                cin >> output_file;

                compressed = output_file + ".abdul";

                writeInfo(image, compressed, write_pos);
                image.P2Compress(write_pos, compress_file, compressed);
            }
            else
            {
                cerr << "Invalid file format";
                exit(1);
            }
        }
        else if (choice == '2')
        {
            cout << "Please enter the full path of the file you want to decompress below:\n";
            cin >> compress_file;

            streampos pos;
            Compression image = readInfo(compress_file, pos);

            if (image.P2Check())
            {
                cout << "\nWhat do you want the decompressed image to be? \nWrite the name down below:\n";
                cin >> output_file;

                compressed = output_file + ".pgm";

                writeInfo(image, compressed, pos);
                image.P2Decompress(compress_file, compressed, pos);
            }
            else
            {
                cerr << "Invalid file format!";
                exit(1);
            }
        }
        else
        {
            cerr << "Invalid option";
            exit(1);
        }
    }

    return 0;
}