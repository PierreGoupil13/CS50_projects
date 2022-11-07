import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")


# TODO: Read database file into a variable
    # Create a dict to store the database in
    dna_base = []
    dna_seq = []
    # Open the csv file
    with open(sys.argv[1]) as db:
        # Create a reader for the DB
        db_seqReader = csv.reader(db)
        # Read every item in the reader
        for row in db_seqReader:
            # Store each item in the dict
            dna_base.append(row)

    # Make a list of all the STR's to consider
    dna_seq = dna_base[0]
    del dna_base[0]
    # Delete the 'name' object
    del dna_seq[0]

    # TODO: Read DNA sequence file into a variable
    # Open the file and read the DNA into a variable
    seq = open(sys.argv[2])
    sequence = seq.read()

    # TODO: Find longest match of each STR in DNA sequence
    # Create a list to store the matches
    matches = []

    # Iterate trought the possible STR's
    for item in dna_seq:
        # Find the longest match for this STR
        run = longest_match(sequence, item)
        # Append the result to the list
        matches.append(run)

    # TODO: Check database for matching profiles
    # Iterate throught every person
    for people in dna_base:
        check = False
        i = 0

        # Iterate over every STR matches
        for x in matches:
            x1 = int(people[i + 1])
            x2 = int(matches[i])
            # If there is no match, go to the newt person
            if x1 != x2:
                check = False
                break
            # Else, check for the next STR
            else:
                check = True
                i += 1

        # If a person has every STR count like the sequence, then there is a match
        if check == True:
            print(people[0])
            return
    # Else print no match
    print('No match')
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
