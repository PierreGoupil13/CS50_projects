import entier as e
import math

quarter = 0.25
dime = 0.10
nickel = 0.05
penny = 0.01


def main():

    # Prompt the user to get the amount
    amount = e.get_float("Change owed : ")

    while amount < 0:
        amount = e.get_float("Change owed : ")

    # Initialize a change variable to keep track of the number of coins
    change = 0
    reste = 0
    # Change for quarters

    # Get the number of quaters
    change = get_quarters(amount)
    # Set the amount left after change
    reste = round(amount - (change * quarter), 2)

    # Change for the dimes
    if reste >= dime:
        coins = get_dime(reste)
        reste = round(reste - (coins * dime), 2)
        change += coins

    # Change for nickels
    if reste >= nickel:
        coins = get_nickels(reste)
        reste = round(reste - (coins * nickel), 2)
        change += coins

    # Change for pennies
    if reste >= penny:
        coins = get_pennies(reste)
        reste = round(reste - (coins * penny), 2)
        change += coins

    print(int(change))


def get_quarters(amount):

    # Get the number of coins and rounds it to the first inferior integer
    coins = math.floor(amount / quarter)
    print(coins)

    return coins


def get_dime(amount):

    # Get the number of coins and rounds it to the first inferior integer
    coins = math.floor(amount / dime)

    return coins


def get_nickels(amount):

    # Get the number of coins and rounds it to the first inferior integer
    coins = math.floor(amount / nickel)

    return coins


def get_pennies(amount):

    # Get the number of coins and rounds it to the first inferior integer
    coins = math.floor(amount / penny)

    return coins


if __name__ == "__main__":
    main()