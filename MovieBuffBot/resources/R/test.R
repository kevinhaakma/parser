library("DBI")
library("RMySQL")

#kevin R
con <- dbConnect(MySQL(), dbname="imdb", user="root", password="kevinhaakma")
values <- dbGetQuery(con, "select count(name) as count from actors")

invisible(jpeg('c:/temp/output.jpg'))
barplot(values$count, horiz=FALSE, cex.names=0.5)
invisible(dev.off())
