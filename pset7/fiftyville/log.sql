-- Keep a log of any SQL queries you execute as you solve the mystery.


--All the crimes that happned in the street the month of the crime
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street" AND month = 7;
-- We know that it happened at 10:15 AM at a bakery
-- Interview did on the same day, 3 person interviewed at the same time


--Let's read the interviews
SELECT transcript FROM interviews
WHERE year = 2021
    AND day = 28
    AND month = 7
    AND transcript LIKE "%bakery%";
-- We have 3 leads : The car he used to escape (look at the footage), He withdrawed cash on Leggett Street earlier in the morning,
-- and him and his accomplice took the first flight the next day.


-- Let's find the licence plate of the car
SELECT license_plate, activity FROM bakery_security_logs
WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute > 20;
-- We can safely assume that the plate is one of the fourth : L93JTIZ ; 322W7JE ; 0NTHK55 ; 1106N58


-- List of all the flights that departed from Fiftyville
SELECT id, destination_airport_id, hour FROM flights
WHERE origin_airport_id IN (
    SELECT id FROM airports
    WHERE full_name = "Fiftyville Regional Airport"
)
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour;
-- 2 credible flights, the id are 1 et 4 at respectivly 9 and 8 Am

-- Compare to flight from early morning
SELECT id, destination_airport_id, hour FROM flights
WHERE origin_airport_id IN (
    SELECT id FROM airports
    WHERE full_name = "Fiftyville Regional Airport"
)
AND year = 2021
AND month = 7
AND day = 29
AND id IN (
    SELECT flight_id FROM passengers
WHERE passport_number IN (
    -- Donne la liste des passeport qui match avec les plaques
    SELECT passport_number FROM people
    WHERE phone_number in (
        SELECT caller FROM phone_calls
        WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 100
            -- Donne la liste des plaques
            AND caller in (SELECT phone_number FROM people
        WHERE license_plate IN (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND minute > 20)
    )
)
)
)
ORDER BY hour;
-- Gives me the flight id 36 who goes to the airport number 4 at 8 am that one of the passenger I found was in
-- Flight is probably the id 36 going to airports n°4 at 8 am

-- Getting all th bit and pieces together
SELECT city FROM airports
WHERE id = 4;
-- City should be NYC


-- So I have the City and the Flight, now let's see who was in that plane
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = 36;
-- Gives me a list of the passengers (List 1)

-- Let's make a list of people who withdraw cash on that day
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number IN (
    SELECT account_number FROM atm_transactions
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND transaction_type = "withdraw"
        AND atm_location = "Leggett Street"
);
-- List 2 is the list of people who did that


-- List the people that phone called within 10 min of the robbery
SELECT name FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration < 70
);
-- List 3 is done


-- List of cars that leave the bakery
SELECT name FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND minute < 20
);

-- 3 names stand out for now. Let's dig more
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = 36
INTERSECT
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number IN (
    SELECT account_number FROM atm_transactions
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND transaction_type = "withdraw"
        AND atm_location = "Leggett Street"
)
INTERSECT
SELECT name FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration < 70
)
INTERSECT
SELECT name FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND minute < 20
);
-- The only person that match all the list is Bruce


-- Now let's find who he called
SELECT name FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration < 70
        AND caller = (
            SELECT phone_number FROM people
            WHERE name = "Bruce"
        )
);
-- I get the name Robin

-- So the thief is Bruce who escaped to NYC with the help of Bruce.