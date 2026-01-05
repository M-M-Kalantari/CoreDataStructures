#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <cstring>
#include <algorithm>

using namespace std;

class MyString {
private:
    char *str; // [0] = length, [1..length] = characters

    // Return length of string
    int length() const {
        return str ? (unsigned char) str[0] : 0;
    }

    // Replace current string with new content
    void replace(int newLen, const char *source, int offset = 0) {
        delete[] str;
        str = new char[newLen + 1];
        str[0] = (char) newLen;
        if (newLen > 0) memcpy(str + 1, source + offset, newLen);
    }

public:
    // Constructor: create string from std::string
    MyString(const string &input) {
        int len = input.length();
        str = new char[len + 1];
        str[0] = (char) len;
        memcpy(str + 1, input.c_str(), len);
    }

    // Destructor: free memory
    ~MyString() {
        delete[] str;
    }

    // Return the length of the string
    int my_string_len() {
        return length();
    }

    // Insert character 'c' at index
    void my_string_insert(char c, int index) {
        int oldLen = length();
        if (index < 0 || index > oldLen) return;

        int newLen = oldLen + 1;
        char *newStr = new char[newLen + 1];
        newStr[0] = (char) newLen;
        int k = 1;

        // Copy characters before index
        for (int i = 1; i <= index; i++) newStr[k++] = str[i];
        // Insert new char
        newStr[k++] = c;
        // Copy characters after index
        for (int i = index + 1; i <= oldLen; i++) newStr[k++] = str[i];

        delete[] str;
        str = newStr;
    }

    // Delete character at a specific index
    void my_string_delete_char_from(int index) {
        int oldLen = length();
        if (index < 0 || index >= oldLen) return;

        int newLen = oldLen - 1;
        char *newStr = new char[newLen + 1];
        newStr[0] = (char) newLen;
        int k = 1;

        // Copy characters before the index
        for (int i = 1; i <= index; i++) newStr[k++] = str[i];
        // Skip the character at index and copy the rest
        for (int i = index + 2; i <= oldLen; i++) newStr[k++] = str[i];

        delete[] str;
        str = newStr;
    }

    // Delete all occurrences of character 'c'
    void my_string_delete_char(char c) {
        int oldLen = length(), newLen = 0;
        // Count characters that are not 'c'
        for (int i = 1; i <= oldLen; i++)
            if (str[i] != c) newLen++;

        char *newStr = new char[newLen + 1];
        newStr[0] = (char) newLen;
        int k = 1;
        for (int i = 1; i <= oldLen; i++)
            if (str[i] != c) newStr[k++] = str[i];

        delete[] str;
        str = newStr;
    }

    // Keep only substring from start to end indices
    void my_string_separate(int start, int end) {
        int oldLen = length();
        start = max(0, start);
        end = min(oldLen - 1, end);
        if (start > end) {
            replace(0, nullptr); // empty string
            return;
        }
        replace(end - start + 1, str + 1 + start);
    }

    // Find first occurrence of character 'c', return index or -1
    int my_string_find_char(char c) {
        for (int i = 1; i <= length(); i++)
            if (str[i] == c) return i - 1;
        return -1;
    }

    // Compare with another MyString
    bool my_string_equal(const MyString &other) {
        int len = length();
        if (len != other.length()) return false;
        return memcmp(str + 1, other.str + 1, len) == 0;
    }

    // Concatenate another MyString at the end
    void my_string_concat(const MyString &other) {
        int len1 = length(), len2 = other.length();
        char *newStr = new char[len1 + len2 + 1];
        newStr[0] = (char) (len1 + len2);
        memcpy(newStr + 1, str + 1, len1);
        memcpy(newStr + 1 + len1, other.str + 1, len2);
        delete[] str;
        str = newStr;
    }

    // Convert all letters to uppercase
    void my_string_to_upper_case() {
        for (int i = 1; i <= length(); i++)
            if (str[i] >= 'a' && str[i] <= 'z') str[i] -= 32;
    }

    // Convert all letters to lowercase
    void my_string_to_lower_case() {
        for (int i = 1; i <= length(); i++)
            if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
    }

    // Find substring, return starting index or -1
    int my_string_find_string(const MyString &other) {
        int len1 = length(), len2 = other.length();
        if (len2 == 0) return 0;
        if (len2 > len1) return -1;
        for (int i = 1; i <= len1 - len2 + 1; i++)
            if (memcmp(str + i, other.str + 1, len2) == 0) return i - 1;
        return -1;
    }

    // Print string to console
    void my_string_print() const {
        for (int i = 1; i <= length(); i++) cout << str[i];
        cout << endl;
    }
};

// -------- Interactive menu --------
int main() {
    cout << "Enter initial string: ";
    string input;
    getline(cin, input);
    MyString myStr(input);

    while (true) {
        cout << "\n--- Menu ---\n";
        cout << "1. Length\n";
        cout << "2. Insert char\n";
        cout << "3. Delete from index\n";
        cout << "4. Delete char\n";
        cout << "5. Separate substring\n";
        cout << "6. Find char\n";
        cout << "7. Equal\n";
        cout << "8. Concat\n";
        cout << "9. To Upper\n";
        cout << "10. To Lower\n";
        cout << "11. Find string\n";
        cout << "12. Print\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) break;

        switch (choice) {
            case 1:
                cout << "Length: " << myStr.my_string_len() << endl;
                break;

            case 2: {
                // Insert char
                char c;
                int idx;
                cout << "Enter character to insert: ";
                cin >> c;
                cout << "Enter index to insert at: ";
                cin >> idx;
                myStr.my_string_insert(c, idx);
                myStr.my_string_print();
                break;
            }

            case 3: {
                // Delete from index
                int idx;
                cout << "Enter index to delete from: ";
                cin >> idx;
                myStr.my_string_delete_char_from(idx);
                myStr.my_string_print();
                break;
            }

            case 4: {
                // Delete char
                char c;
                cout << "Enter character to delete: ";
                cin >> c;
                myStr.my_string_delete_char(c);
                myStr.my_string_print();
                break;
            }

            case 5: {
                // Separate substring
                int start, end;
                cout << "Enter start index: ";
                cin >> start;
                cout << "Enter end index: ";
                cin >> end;
                myStr.my_string_separate(start, end);
                myStr.my_string_print();
                break;
            }

            case 6: {
                // Find char
                char c;
                cout << "Enter character to find: ";
                cin >> c;
                cout << "Index: " << myStr.my_string_find_char(c) << endl;
                break;
            }

            case 7: {
                // Equal
                string s;
                cout << "Enter string to compare: ";
                getline(cin, s);
                MyString temp(s);
                cout << boolalpha << myStr.my_string_equal(temp) << endl;
                break;
            }

            case 8: {
                // Concat
                string s;
                cout << "Enter string to concatenate: ";
                getline(cin, s);
                MyString temp(s);
                myStr.my_string_concat(temp);
                myStr.my_string_print();
                break;
            }

            case 9: // To Upper
                myStr.my_string_to_upper_case();
                myStr.my_string_print();
                break;

            case 10: // To Lower
                myStr.my_string_to_lower_case();
                myStr.my_string_print();
                break;

            case 11: {
                // Find string
                string s;
                cout << "Enter string to find: ";
                getline(cin, s);
                MyString temp(s);
                cout << "Index: " << myStr.my_string_find_string(temp) << endl;
                break;
            }

            case 12:
                // Print
                myStr.my_string_print();
                break;

            default:
                cout << "Invalid option\n";
                break;
        }

        // Clear input buffer for next loop
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}
