#include <stdio.h>
#include <string.h>

int matches(const char *pattern, const char *str) {
    
    if (*pattern == '\0') //μοτίβο είναι κενό, όνομα αρχείου πρέπει κενό.
            return *str == '\0';
 
    if (*pattern == '*')// Αν το πρώτο χαρακτήρα του μοτίβου είναι '*' 
    {
        // Ελέγχουμε αν το επόμενο μέρος του μοτίβου ταιριάζει με το υπόλοιπο string
        // ή αν το τρέχον χαρακτήρα του string μπορεί να αντιστοιχεί με το '*'.
       
	    int result1 = matches(pattern + 1, str);  // Αντιστοίχιση με το επόμενο χαρακτήρα του μοτίβου.
	    int result2 = 0;

	    if (*str != '\0') 
         		result2 = matches(pattern, str + 1);  //αντιστοιχούμε το pattern με το επόμενο χαρακτήρα του string.
	    return result1 || result2;  // Επιστρέφουμε το λογικό OR των δύο αποτελεσμάτων.
    }

    if (*pattern == *str)// ifr first chars are same we continue to the next
        return matches(pattern + 1, str + 1);

    return 0; //if not match
}

// return matches(pattern + 1, str) || (*str != '\0' && matches(pattern, str + 1));












int main() {
    // Παράδειγμα χρήσης
    const char *pattern1 = "f*";
    const char *pattern2 = "*f";
    
    const char *files[] = {
        "file1.txt",
        "file2.txt",
        "otherfile.txt",
        "fancy.txt",
        "testf",
        "f",
        "nofmatch"
    };

    printf("Files matching '%s':\n", pattern1);
    for (int i = 0; i < 7; i++) {
        if (matches(pattern1, files[i])) {
            printf("%s\n", files[i]);
        }
    }

    printf("\nFiles matching '%s':\n", pattern2);
    for (int i = 0; i < 7; i++) {
        if (matches(pattern2, files[i])) {
            printf("%s\n", files[i]);
        }
    }

    return 0;
}

