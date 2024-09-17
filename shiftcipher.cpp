#include <iostream>
#include <string>
using namespace std;

string caesar_encrypt(const string& plain_text, int shift) {
    string cipher_text = "";

    for (char c : plain_text) {
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            cipher_text += (c - offset + shift) % 26 + offset;
        } else {
            cipher_text += c;
        }
    }

    return cipher_text;
}

string caesar_decrypt(const string& cipher_text, int shift) {
    string plain_text = "";

    for (char c : cipher_text) {
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            plain_text += (c - offset - shift + 26) % 26 + offset;
        } else {
            plain_text += c;
        }
    }

    return plain_text;
}

int main() {
    string text;
    int shift;

    cout << "Masukkan teks: ";
    getline(cin, text);

    cout << "Masukkan jumlah geseran : ";
    cin >> shift;

    string encrypted = caesar_encrypt(text, shift);
    cout << "Hasil Enkripsi: " << encrypted << endl;

    string decrypted = caesar_decrypt(encrypted, shift);
    cout << "Hasil Dekripsi: " << decrypted << endl;

    return 0;
}
