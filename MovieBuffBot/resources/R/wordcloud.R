#!/usr/bin/Rscript

# install.packages("RMySQL")
library(RMySQL)

con <- dbConnect(MySQL(), dbname="imdb", user="imdb", password="imdb")
values <- dbGetQuery(con, "jdbc localhost 3306 imdb imdb imdb select actors.Actor as actorname, count(roles.ActorID) as countroles from roles, actors, movies, countries where roles.MovieID = movies.MovieID and roles.ActorID = actors.ActorID and countries.MovieID = movies.MovieID and Country ='<star>'")

invisible(jpeg('/tmp/video-format.jpg'))
barplot(values$freq, names.arg = values$format, horiz=FALSE, cex.names=0.5)
invisible(dev.off())

