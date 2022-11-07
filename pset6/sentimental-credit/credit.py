# TODO
import re
import cardCheck


def main():

    cardNumber = input("Enter a credit card number : ")

    # Check if it is a Amex card
    if re.findall("^34|^37", cardNumber):
        if cardCheck.is_amex(cardNumber):
            print("AMEX")
        else:
            print("INVALID")
    # Check if Master
    elif re.findall("^51|^52|^53|^54|^55", cardNumber):
        if cardCheck.is_master(cardNumber):
            print("MASTERCARD")
        else:
            print("INVALID")
    # Check if Visa
    elif re.findall("^4", cardNumber):
        if cardCheck.is_visa(cardNumber):
            print("VISA")
        else:
            print("INVALID")
    # It means the card is Invalid
    else:
        print("INVALID")


if __name__ == "__main__":
    main()