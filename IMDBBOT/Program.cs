using DSharpPlus;
using DSharpPlus.VoiceNext;
using DSharpPlus.CommandsNext;
using System.Threading.Tasks;
using RDotNet;

namespace IMDBBOT
{
    /* DOCUMENTATION
     * https://discordapp.com/developers/docs/intro discord app documentation
     * https://dsharpplus.emzi0767.com/api/index.html dsharp library documentation
     */

    class Program
    {
        public static DiscordClient discord;
        static CommandsNextModule commands;
        static VoiceNextClient voice;

        static void Main(string[] args)
        {
            MainAsync(args).ConfigureAwait(false).GetAwaiter().GetResult();
        }

        static async Task MainAsync(string[] args)
        {
            discord = new DiscordClient(new DiscordConfiguration
            {
                Token = "NTU0NjQ4NTk4NzEzOTkxMTg4.D3llfQ.x9v_J1_Zhf55TPDWfpBSTPuU-ok", //Put Discord App token here
                TokenType = TokenType.Bot,
                UseInternalLogHandler = true,
                LogLevel = LogLevel.Debug
            });

            discord.MessageCreated += async e =>
            {
                if (e.Message.Content.ToLower().StartsWith("hoi"))
                    await e.Message.RespondAsync("doei");

                else if (e.Message.Content.ToLower().StartsWith("hallo"))
                    await e.Message.RespondAsync("??");
            };

            commands = discord.UseCommandsNext(new CommandsNextConfiguration
            {
                EnableDms = false,
                StringPrefix = "!" //Prefix for the Discord commands
            });

            commands.RegisterCommands<Commands>(); //Reference to the Commands.cs file

            voice = discord.UseVoiceNext();

            await discord.ConnectAsync();
            await Task.Delay(-1);
        }
    }
}
