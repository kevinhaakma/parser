#!/usr/bin/Rscript

# install.packages("RMySQL")
library(RMySQL)

#wiebe R
#db connection
con <- dbConnect(MySQL(), dbname="imdb", user="root", password="sql080")

#values
values <- dbGetQuery(con, "select count(roles.ActorID) as countRoles, movies.Year as movieYear, ratings.Votes as allVotes from roles, movies, ratings where roles.Movie = movies.Movie and movies.Movie = ratings.Title")

#model
model <-glm(allVotes~countRoles+movieYear,data=values,family=binomial)
summary(model)

#prediction
#predictTest <-predict(model,type="response")

#library roc
#library(ROCR)
#ROCRperfi <-performance(predictTest,"tpr","fpr")

#ROC plot
#invisible(jpeg('/tmp/factoren.jpg'))
#plot(ROCRperfi,colorize=true,print.cutoffs.at=seq(0,1,0.1))
#invisible(dev.off())
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



