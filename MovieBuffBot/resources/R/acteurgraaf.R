#!/usr/bin/Rscript

# install.packages("RMySQL")
library(RMySQL)

#wiebe R
con <- dbConnect(MySQL(), dbname="imdb", user="root", password="sql080")
values <- dbGetQuery(con, "select actors.Actor as actorname, count(roles.ActorID) as countroles from roles, actors, movies where roles.MovieID = movies.MovieID and roles.ActorID = actors.ActorID")

invisible(jpeg('/tmp/movieroles.jpg'))
barplot(values$countroles, names.arg = values$actorname, horiz=FALSE, cex.names=0.5)
invisible(dev.off())

