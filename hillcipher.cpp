#include <iostream>
#include <vector>

using namespace std;

// Mengalikan dua matriks 2x2 dengan vektor pasangan huruf dan mod 26
vector<int> matrixMultiplyMod26(vector<vector<int>> key, vector<int> textPair) {
    return {(key[0][0] * textPair[0] + key[0][1] * textPair[1]) % 26,
            (key[1][0] * textPair[0] + key[1][1] * textPair[1]) % 26};
}

// Menghitung invers matriks 2x2 mod 26
vector<vector<int>> inverseMatrixMod26(vector<vector<int>> key) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    if (det < 0) det += 26;
    int detInv = 0;
    for (int i = 0; i < 26; i++) {
        if ((det * i) % 26 == 1) {
            detInv = i;
            break;
        }
    }
    vector<vector<int>> invKey = {{(key[1][1] * detInv) % 26, (-key[0][1] * detInv) % 26},
                                  {(-key[1][0] * detInv) % 26, (key[0][0] * detInv) % 26}};
    for (auto& row : invKey) for (auto& val : row) if (val < 0) val += 26;
    return invKey;
}

// Fungsi enkripsi
string encrypt(string text, vector<vector<int>> key) {
    string result = "";
    for (int i = 0; i < text.length(); i += 2) {
        vector<int> pair = {text[i] - 'A', text[i + 1] - 'A'};
        vector<int> encryptedPair = matrixMultiplyMod26(key, pair);
        result += (encryptedPair[0] + 'A');
        result += (encryptedPair[1] + 'A');
    }
    return result;
}

// Fungsi dekripsi
string decrypt(string text, vector<vector<int>> key) {
    vector<vector<int>> invKey = inverseMatrixMod26(key);
    return encrypt(text, invKey);  // Menggunakan enkripsi dengan matriks invers untuk dekripsi
}

// Fungsi untuk mencari kunci cipher berdasarkan plaintext dan ciphertext
vector<vector<int>> findKey(string plaintext, string ciphertext) {
    vector<vector<int>> ptPairs = {{plaintext[0] - 'A', plaintext[1] - 'A'},
                                   {plaintext[2] - 'A', plaintext[3] - 'A'}};
    vector<vector<int>> ctPairs = {{ciphertext[0] - 'A', ciphertext[1] - 'A'},
                                   {ciphertext[2] - 'A', ciphertext[3] - 'A'}};
    
    // Mencari invers dari pasangan huruf plaintext
    vector<vector<int>> invPt = inverseMatrixMod26(ptPairs);
    
    // Mengalikan matriks ciphertext dengan invers plaintext untuk mendapatkan kunci
    vector<vector<int>> key(2, vector<int>(2));
    key[0][0] = (ctPairs[0][0] * invPt[0][0] + ctPairs[0][1] * invPt[1][0]) % 26;
    key[0][1] = (ctPairs[0][0] * invPt[0][1] + ctPairs[0][1] * invPt[1][1]) % 26;
    key[1][0] = (ctPairs[1][0] * invPt[0][0] + ctPairs[1][1] * invPt[1][0]) % 26;
    key[1][1] = (ctPairs[1][0] * invPt[0][1] + ctPairs[1][1] * invPt[1][1]) % 26;

    return key;
}

int main() {
    int choice;
    cout << "Pilih operasi: " << endl;
    cout << "1. Enkripsi (cari ciphertext)" << endl;
    cout << "2. Dekripsi (cari plaintext)" << endl;
    cout << "3. Cari kunci cipher" << endl;
    cout << "Pilihan: ";
    cin >> choice;

    if (choice == 1) {
        string plaintext;
        vector<vector<int>> key(2, vector<int>(2));
        cout << "Masukkan plaintext (panjang genap, hanya huruf besar): ";
        cin >> plaintext;
        cout << "Masukkan matriks kunci (2x2): ";
        cin >> key[0][0] >> key[0][1] >> key[1][0] >> key[1][1];
        string ciphertext = encrypt(plaintext, key);
        cout << "Ciphertext: " << ciphertext << endl;
    } else if (choice == 2) {
        string ciphertext;
        vector<vector<int>> key(2, vector<int>(2));
        cout << "Masukkan ciphertext (panjang genap, hanya huruf besar): ";
        cin >> ciphertext;
        cout << "Masukkan matriks kunci (2x2): ";
        cin >> key[0][0] >> key[0][1] >> key[1][0] >> key[1][1];
        string plaintext = decrypt(ciphertext, key);
        cout << "Plaintext: " << plaintext << endl;
    } else if (choice == 3) {
        string plaintext, ciphertext;
        cout << "Masukkan plaintext (4 huruf, hanya huruf besar): ";
        cin >> plaintext;
        cout << "Masukkan ciphertext (4 huruf, hanya huruf besar): ";
        cin >> ciphertext;
        vector<vector<int>> key = findKey(plaintext, ciphertext);
        cout << "Kunci cipher (2x2): " << endl;
        cout << key[0][0] << " " << key[0][1] << endl;
        cout << key[1][0] << " " << key[1][1] << endl;
    } else {
        cout << "Pilihan tidak valid!" << endl;
    }

    return 0;
}
