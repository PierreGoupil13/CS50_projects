# TODO
from cs50 import get_string
import re


def main():
    text = get_string("Text to analyze : ")

    # Count the number of letters in the text
    letters = re.findall("[a-zA-Z]", text)

    # Get the list of  all the words and punctuation (to din the sentences) in the text
    wordList = re.split("\s", text)
    sent = re.findall("[.!?]", text)

    # Get the number of words and sentences
    words = len(wordList)
    sentences = len(sent)

    # Compute the numbers of words sentences and letters througth the Colleman Liau formula
    grade = get_grade(words, sentences, len(letters))

    print_grade(grade)


def get_grade(numWords, numSentences, numLetters):

    # Get the average of letters per 100 words in the text
    L = ((numLetters / numWords) * 100)
    # Get the average of sentences per 100 words in the text
    S = ((numSentences / numWords) * 100)

    grade = round((0.0588 * L) - (0.296 * S) - 15.8)

    return grade


def print_grade(grade):
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


if __name__ == "__main__":
    main()