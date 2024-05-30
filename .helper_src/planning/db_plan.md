## title.principals
- ```tconst, ordering, nconst, category, job, characters```
## name.basics
- ```nconst, primaryName, birthYear, deathYear, primaryProfession, knownForTitles```
## title.basics
- ```tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres```
## title.crew
- ```tconst, directors, writers```
## title.ratings
- ```tconst, averageRating, numVotes```
1. First, we will set up a database with tables for all of these files.
1.1. principals table: primary unique id, tconst, ordering, nconst, category, job, characters
1.2. name_info table: primary unique nconst, primaryName, birthYear, deathYear, primaryProfession, knownForTitles
1.3. film_info table: primary unique tconst, titleType, primaryTitle, isAdult, startYear, endYear, runtimeMinutes
1.4. crew table: primary unique tconst, directors
1.5. ratings table: primary unique tconst, averageRating
2. Then, we will eliminate all records in which ```averageRating < 8.0``` from the ratings table
3. 