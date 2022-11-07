# TODO
import entier


def main():
    # Making a sort of do while loop to prompt the user
    while(True):
        height = entier.get_int("Enter the height : ")
        if height < 9 and height > 0:
            break
        # Reprompt the user
        else:
            print("The height you entered is not correct")

    pyramide_maker(height)


def pyramide_maker(height):
    # Print a half pyramide
    for i in range(height):
        print(" " * (height - (i+1)), end="")
        print("#" * (i+1), end="")
        print("  ", end="")
        print("#" * (i+1))


if __name__ == "__main__":
    main()
