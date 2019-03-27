using RDotNet;
using System;
using System.Threading.Tasks;
using DSharpPlus.Entities;
using DSharpPlus.VoiceNext;
using DSharpPlus.CommandsNext;
using DSharpPlus.CommandsNext.Attributes;

namespace IMDBBOT
{
    class Commands
    {
        /// <summary>
        /// Basic "!Hi" Command, The bot will respond with "👋 Hi" and metion your Discord username. Aliases: !Hi, !H, !h.
        /// </summary>
        /// <param name="ctx">CTX is the command context and contains the Username of the user requested the command what channel the user is in etc.</param>
        /// <returns></returns>
        [Command("hi"), Description("The bot waves at you saying your name."), Aliases("Hi", "H", "h")]
        public async Task Hi(CommandContext ctx)
        {
            await ctx.RespondAsync($"👋 Hi, {ctx.User.Mention}!");
        }

        [Command("join"), Description("The bot joins your voice channel."), Aliases("Join", "J", "j")]
        public async Task Join(CommandContext ctx)
        {
            var vnext = ctx.Client.GetVoiceNextClient();

            var vnc = vnext.GetConnection(ctx.Guild);
            if (vnc == null)
            {
                var chn = ctx.Member?.VoiceState?.Channel;
                if (chn == null)
                    throw new InvalidOperationException("You need to be in a voice channel.");

                vnc = await vnext.ConnectAsync(chn);
                await ctx.Message.CreateReactionAsync(DiscordEmoji.FromName(ctx.Client, ":heart:"));
            }
            else if (ctx.Message.Content.Contains("join"))
                await ctx.Message.CreateReactionAsync(DiscordEmoji.FromName(ctx.Client, ":rage:"));
        }

        [Command("leave"), Description("The bot leaves your voice channel."), Aliases("Leave", "L", "l")]
        public async Task Leave(CommandContext ctx)
        {
            var vnc = ctx.Client.GetVoiceNextClient().GetConnection(ctx.Guild);
            vnc.Disconnect();

            await ctx.Message.CreateReactionAsync(DiscordEmoji.FromName(ctx.Client, ":broken_heart:"));
        }

        [Command("r")]
        public async Task r(CommandContext ctx)
        {
            //NOTE FOR MAKING RDONET WORKING IN C
            //INSTALL R3.4.4 : https://cran.r-project.org/bin/windows/base/old/3.4.4/
            //INSTALL System.Security.Permission Nuget

            REngine engine;

            //init the R engine            
            REngine.SetEnvironmentVariables();
            engine = REngine.GetInstance();

            if (engine.IsRunning == false)
            {
                engine.Initialize();
            }

            engine.Evaluate("Data <- read.csv(\"crimepubs.csv\")");

            string fileName = "C:\\temp\\myplot.png";

            CharacterVector fileNameVector = engine.CreateCharacterVector(new[] { fileName });
            engine.SetSymbol("fileName", fileNameVector);
            engine.Evaluate("png(filename=fileName, width=6, height=6, units='in', res=100)");
            engine.Evaluate("plot(Data)");
            engine.Evaluate("dev.off()");
            //clean up
            engine.Dispose();

            await ctx.Channel.SendFileAsync(fileName, "hello");
        }
    }
}
