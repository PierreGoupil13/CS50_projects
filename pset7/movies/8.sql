SELECT people.name FROM movies JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id WHERE movies.title = "Toy Story";