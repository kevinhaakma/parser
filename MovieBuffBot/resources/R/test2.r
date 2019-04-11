#!C:\Program Files\R\R-3.5.2\bin\Rscript

#install.packages("RPostgreSQL")
require("RPostgreSQL")

drv <- dbDriver("PostgreSQL")
con <- dbConnect(drv, dbname = "imdb", host = "localhost", port = 5432, user = "postgres", password = "imdb")

values <- dbGetQuery(con, "select startyear, avg(averagerating) as rating from title_ratings join title_basics on title_basics.tconst = title_ratings.tconst where titletype = 'movie' and startyear is not null group by (startyear)")

invisible(png('c:/tmp/ratingyears.png', width = 5, height = 5, units = 'in', res = 400))
#barplot(values$rating, names.arg = values$startyear, horiz=FALSE, cex.names=0.5)
plot(values)
invisible(dev.off())

invisible(dbDisconnect(con))
invisible(dbUnloadDriver(drv))