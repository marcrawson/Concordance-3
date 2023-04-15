# Concordance 3

### Overview
Concordance algorithm in C generates a formatted and sorted text output.

### Algorithm Steps:
- Takes input through *stdin*;
- Identifies and stores **exclusion words** and **body text**;
- Calculates keywords by **matching** non-exclusion words with body text;
- Locates keyword occurances;
- Formats output by **aligning keywords** and **removing excess context**;
- Result is output through *stdout*.


### Text Concordance
Concordance algorithms, also known as keyword in context algorithms, analyze the context of a given word by examining the words on either side of it. The Concordance 3 algorithm focuses on all the words in the body text that are not part of the exclusion words list, which are called query words. For example, if the query word is "apple," and the sentence is "An apple fell beside me," the raw output before formatting would be "An APPLE fell beside me."

However, Concordance3 takes the concept further by enhancing the output's readability and consistency. Specifically, it sorts all query words lexicographically and aligns them in columns. The Concordance3 program is a valuable tool for data analysis applications because it not only identifies the frequency of a given word but also the context in which the word is used. This technique can provide significant insight into large datasets, which would otherwise be hidden.

To ensure the Concordance3 program's maintainability and ease of debugging, it employs efficient software engineering practices, such as low coupling and high cohesion. The program decomposes larger functions into smaller helper functions, each with specific documentation. The algorithm also uses dynamic allocation in C through a custom memory allocation function called "emalloc." Data is primarily stored using the linked-list data structure, which provides efficient and readable data processing.

### Running the program

Compile: `gcc -Wall concord3.c -o concord3`

Execute: `cat [input_file].txt | ./concord3`
