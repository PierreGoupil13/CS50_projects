import math

def is_amex(cardNumber):
    if len(cardNumber) == 15:
        if algo_luhn(cardNumber):
            return True

    return False


def is_master(cardNumber):
    if len(cardNumber) == 16:
        if algo_luhn(cardNumber):
            return True

    return False


def is_visa(cardNumber):
    if len(cardNumber) in (13, 16):
        if algo_luhn(cardNumber):
            return True

    return False


# ATTENTION : comme les indexes commence a 0, si la taille est pair alors les chiffres a multiplié sont aussi PAIR et non IMPAIR (j'ai galerer a cause de ca)

def algo_luhn(cardNumber):

    # Creer une list car j'ai decider de travailler avec une string comme numero de carte
    temp = list(cardNumber)
    sum = 0
    # Creer une var de taille pour avoir un code plus lisible
    taille = len(cardNumber)

    # Si la taille de la carte est impair alors les chiffres a multiplie seront les indexes impair
    if (taille % 2) != 0:
        # Loop sur toute la liste
        for i in range(taille):
            if (i % 2) != 0:
                tempNum = int(temp[i]) * 2
                # Si le tempNum est a deux chiffres, il faut les separer pour les ajouter a la somme
                if tempNum > 9:
                    # Recupere le dernier chiffre avec le modulo
                    num = (tempNum % 10)
                    # Recupere le premier chiffre en divisant et arrondi a l'entier inferieur (sinon risque d'erreur pour un nombre sup a 14)
                    numBis = math.floor((tempNum / 10))
                    sum += (num + numBis)
                else:
                    sum += round(tempNum)
            else:
                sum += int(temp[i])

    # Si la taille de la carte est impair alors les chiffres a multiplie seront les indexes impair
    else:
        # Meme principe qu'au dessus simplement on inverse les notions de pair et impair
        for i in range(taille):
            if (i % 2) == 0:
                tempNum = int(temp[i]) * 2
                if tempNum > 9:
                    num = (tempNum % 10)
                    numBis = math.floor((tempNum / 10))
                    print(num, numBis)
                    sum += (num + numBis)
                else:
                    sum += round(tempNum)
            else:
                sum += int(temp[i])

    if (sum % 10) == 0:
        return True
    else:
        return False
