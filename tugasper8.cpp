#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

struct Node {
    long long nim;
    string nama;
    bool isOccupied = false;
    bool isDeleted = false;
};

class HashTable {
private:
    Node table[TABLE_SIZE];

    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    int hash1(long long key) {
        return key % TABLE_SIZE;
    }

    int hash2(long long key) {
        int step = 7 - (key % 7);

        while (gcd(step, TABLE_SIZE) != 1) {
            step++;

            if (step >= TABLE_SIZE) {
                step = 1;
            }
        }

        return step;
    }

public:
    void insert(long long nim, string nama) {
        int index = hash1(nim);
        int step = hash2(nim);
        int deletedIndex = -1;

        for (int i = 0; i < TABLE_SIZE; i++) {
            int newIndex = (index + i * step) % TABLE_SIZE;

            if (table[newIndex].isOccupied &&
                table[newIndex].nim == nim) {
                table[newIndex].nama = nama;

                cout << "[UPDATE SUCCESS] Data berhasil diperbarui.\n";
                return;
            }

            if (table[newIndex].isDeleted &&
                deletedIndex == -1) {
                deletedIndex = newIndex;
            }

            if (!table[newIndex].isOccupied &&
                !table[newIndex].isDeleted) {

                if (deletedIndex != -1) {
                    newIndex = deletedIndex;
                }

                table[newIndex].nim = nim;
                table[newIndex].nama = nama;
                table[newIndex].isOccupied = true;
                table[newIndex].isDeleted = false;

                cout << "[INSERT SUCCESS] Data berhasil dimasukkan di indeks "
                     << newIndex << endl;
                return;
            }
        }

        if (deletedIndex != -1) {
            table[deletedIndex].nim = nim;
            table[deletedIndex].nama = nama;
            table[deletedIndex].isOccupied = true;
            table[deletedIndex].isDeleted = false;

            cout << "[INSERT SUCCESS] Data berhasil dimasukkan di indeks "
                 << deletedIndex << endl;
        } else {
            cout << "[INSERT FAILED] Hash Table sudah penuh!\n";
        }
    }

    int search(long long nim) {
        int index = hash1(nim);
        int step = hash2(nim);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int newIndex = (index + i * step) % TABLE_SIZE;

            if (!table[newIndex].isOccupied &&
                !table[newIndex].isDeleted) {
                return -1;
            }

            if (table[newIndex].isOccupied &&
                table[newIndex].nim == nim) {
                return newIndex;
            }
        }

        return -1;
    }

    void remove(long long nim) {
        int index = search(nim);

        if (index != -1) {
            table[index].isOccupied = false;
            table[index].isDeleted = true;

            cout << "[REMOVE SUCCESS] Data berhasil dihapus.\n";
        } else {
            cout << "[REMOVE FAILED] Data tidak ditemukan.\n";
        }
    }

    void display() {
        cout << "\nISI HASH TABLE : \n";
        cout << "Indeks\t| NIM\t\t| Nama Mahasiswa\n";
        cout << "------------------------------------------------\n";

        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].isOccupied) {
                cout << " [" << i << "]\t| "
                     << table[i].nim << "\t| "
                     << table[i].nama << endl;
            } else if (table[i].isDeleted) {
                cout << " [" << i << "]\t| <DELETED>\t| -\n";
            } else {
                cout << " [" << i << "]\t| <EMPTY>\t| -\n";
            }
        }

        cout << "================================================\n";
    }
};

int main() {
    HashTable ht;

    int pilihan;
    long long nim;
    string nama;

    do {
        cout << "\nMENU HASH TABLE (DOUBLE HASHING) :\n";
        cout << "1. Insert Data\n";
        cout << "2. Search Data\n";
        cout << "3. Remove Data\n";
        cout << "4. Display Hash Table\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "\nMasukkan NIM  : ";
                cin >> nim;

                cout << "Masukkan Nama : ";
                getline(cin >> ws, nama);

                ht.insert(nim, nama);
                break;

            case 2:
                cout << "\nMasukkan NIM yang dicari: ";
                cin >> nim;

                {
                    int index = ht.search(nim);

                    if (index != -1) {
                        cout << "[SEARCH SUCCESS] Data ditemukan!\n";
                        cout << "NIM  : " << nim << endl;
                        cout << "Nama : ";
                        ht.display();
                    } else {
                        cout << "[SEARCH FAILED] Data tidak ditemukan.\n";
                    }
                }
                break;

            case 3:
                cout << "\nMasukkan NIM yang ingin dihapus: ";
                cin >> nim;

                ht.remove(nim);
                break;

            case 4:
                ht.display();
                break;

            case 5:
                cout << "\nSeluruh operasi selesai.\n";
                cout << "Menampilkan isi akhir Hash Table...\n";
                ht.display();
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 5);

    return 0;
}
