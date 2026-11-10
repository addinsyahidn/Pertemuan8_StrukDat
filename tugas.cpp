#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
private:
    vector<pair<long long, string>> table;
    vector<int> status;

    int hash1(long long key) {
        return key % TABLE_SIZE;
    }

    int hash2(long long key) {
        return 7 - (key % 7);
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
        status.resize(TABLE_SIZE, 0);
    }

    void insert(long long key, string value) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;
        int deletedIndex = -1;

        while (true) {
            if (status[index] == 1 && table[index].first == key) {
                table[index].second = value;
                cout << "NIM sudah ada, nama diperbarui" << endl;
                return;
            }

            if (status[index] == 2 && deletedIndex == -1) {
                deletedIndex = index;
            }

            if (status[index] == 0) {
                if (deletedIndex != -1) {
                    index = deletedIndex;
                }
                table[index] = make_pair(key, value);
                status[index] = 1;
                cout << "Data berhasil disimpan di slot " << index << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

        if (deletedIndex != -1) {
            table[deletedIndex] = make_pair(key, value);
            status[deletedIndex] = 1;
            cout << "Data berhasil disimpan di slot " << deletedIndex << endl;
        } else {
            cout << "Tabel penuh" << endl;
        }
    }

    void search(long long key) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;

        while (status[index] != 0) {
            if (status[index] == 1 && table[index].first == key) {
                cout << "Data ditemukan di slot " << index << " : " << table[index].second << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

        cout << "Data tidak ditemukan" << endl;
    }

    void remove(long long key) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;

        while (status[index] != 0) {
            if (status[index] == 1 && table[index].first == key) {
                status[index] = 2;
                cout << "Data berhasil dihapus" << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

        cout << "Data tidak ditemukan" << endl;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " : ";

            if (status[i] == 1) {
                cout << table[i].first << " - " << table[i].second;
            } else if (status[i] == 2) {
                cout << "DELETED";
            } else {
                cout << "EMPTY";
            }

            cout << endl;
        }
    }
};

bool isNumber(string s) {
    if (s.empty() || s.length() > 18) {
        return false;
    }
    for (char c : s) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

long long inputNim() {
    string s;
    while (true) {
        cout << "Masukkan NIM : ";
        getline(cin, s);
        if (isNumber(s)) {
            return stoll(s);
        }
        cout << "NIM harus berupa angka (maksimal 18 digit)" << endl;
    }
}

int main() {
    HashTable ht;
    string input, nama;
    char pilihan;

    do {
        cout << "\n1. Insert\n2. Cari\n3. Hapus\n4. Tampilkan\n0. Keluar\nPilihan : ";
        getline(cin, input);
        pilihan = (input.length() == 1) ? input[0] : '-';

        if (pilihan >= '1' && pilihan <= '3') {
            long long nim = inputNim();
            if (pilihan == '1') {
                cout << "Masukkan nama : ";
                getline(cin, nama);
                ht.insert(nim, nama);
            } else if (pilihan == '2') {
                ht.search(nim);
            } else {
                ht.remove(nim);
            }
        } else if (pilihan == '4') {
            ht.display();
        } else if (pilihan != '0') {
            cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != '0');

    return 0;
}
