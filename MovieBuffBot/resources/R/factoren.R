#!/usr/bin/Rscript

# install.packages("RMySQL")
library(RMySQL)
library(DBI)

#wiebe R
#db connection
#con <- dbConnect(MySQL(), dbname="imdb", user="root", password="sql080")
con <- dbConnect(MySQL(), dbname="imdb", user="root", password="sql080")

#values
#values <- dbGetQuery(con, "select count(roles.Actor) as countRoles, movies.Year as movieYear, ratings.Votes as allVotes from roles, movies, ratings where roles.Movie = movies.Movie and movies.Movie = ratings.Title")
#values <- dbGetQuery(con, "select count(roles.Actor) as countRoles, movies.Year as movieYear, ratings.Votes as allVotes from roles, movies, ratings where roles.Movie = movies.Movie and movies.Movie = ratings.Title")
#values <- dbGetQuery(con, "select count(roles_sm.Actor) as countRoles, ratings_sm.Votes as allVotes from roles_sm, ratings_sm where roles_sm.Movie = ratings_sm.Movie")
#values <- dbGetQuery(con, "select count(roles.Actor) as countRoles, ratings.Votes as allVotes from roles, ratings where roles.Movie = ratings.Title limit 0,200")
#values <- dbGetQuery(con, "")

query <- paste("select count(distinct(roles.Actor)) as countRoles, ratings.Votes as allVotes from roles, ratings where roles.Movie = ratings.Title and roles.Movie !='0' and roles.Actor !='0' and ratings.Title !='0' and ratings.Votes !=0 group by ratings.Title order by ratings.Title limit 0,1000")

values <- dbGetQuery(con, query )


#values <- dbGetQuery(con, "")
str(values)
#model
#model <-glm(allVotes~countRoles,data=values,family=binomial)
model <-glm(allVotes~countRoles,data=values)
summary(model)

#prediction
predictTest <-predict(model,type="response")
#predictTest <-predict(model,type="factor")
#predictTest <-predict(model,type="class")
#predictTest <-predict(model,type="numeric")

#library roc
library(ROCR)

#ROCRpred=predict(predictTest,values$countRoles)
ROCRpred=predict(predictTest,values$countRoles,type="numeric")
ROCRperf=performance(ROCRpred,"tpr","fpr")

#ROCRperfi <-performance(predictTest,"tpr","fpr")

#ROC plot
invisible(jpeg('/tmp/factoren.jpg'))
plot(ROCRperfi,colorize=true,print.cutoffs.at=seq(0,1,0.1))
invisible(dev.off())
#abline(0,1)

#AUC
#AUC <-as.numeric(performance(predictTelco,”AUC”)@y.values)
#str(AUC)

#confusion matrix function
#confusion <-function(arg1,arg2,arg3){
#table = table(arg1,arg2>arg3)
#specificity <-table[1,1]/(table[1,1]+table[1,2])
#sensitivity <-table[2,2]/(table[2,1]+table[2,2])
#accuracy <-(table[1,1]+table[2,2])/(table[1,1]+table[1,2]+table[2,1]+table[2,2])
#return(data.frame(Specificity=specificity,Sensitivity=sensitivity,Accuracy=accuracy))}

#show confusion
#confusion(model$serierating,predictTest,0.1)



