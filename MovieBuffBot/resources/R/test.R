library("DBI")
library("RMySQL")

#kevin R
con <- dbConnect(MySQL(), dbname="imdb", user="root", password="sql080")
values <- dbGetQuery(con, "select count(Actor) as count from actors")

invisible(jpeg('C:/temp/output.jpg'))
barplot(values$count, horiz=FALSE, cex.names=0.5)
invisible(dev.off())