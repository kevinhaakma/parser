#!/usr/bin/Rscript

# install.packages("RMySQL")
library(RMySQL)

con <- dbConnect(MySQL(), dbname="imdb", user="imdb", password="imdb")
values <- dbGetQuery(con, "select actors.Actor as actorname, count(roles.ActorID) as countroles, movies.Year as movieyear, ratings.Rating as serierating from roles, actors, movies where roles.MovieID = movies.MovieID and roles.ActorID = actors.ActorID and SerieName !='NULL'")

invisible(jpeg('/tmp/video-format.jpg'))
barplot(values$freq, names.arg = values$format, horiz=FALSE, cex.names=0.5)
invisible(dev.off())

