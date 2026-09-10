const Discord = require('discord.js-selfbot-v13');

const client = new Discord.Client();

let SEU_TOKEN_AQUI = ""
let ID_CONVERSA_AQUI = ""
client.on('ready', async () => {
    console.log(`Bot está online como ${client.user.tag}`);

 
    const user = await client.users.fetch(ID_CONVERSA_AQUI);
    const dmChannel = await user.createDM();

    async function DELETE100() {
        try {
            const fetched = await dmChannel.messages.fetch({ limit: 100 });

            fetched.forEach(async (msg) => {

                if (!msg.system && msg.author.id === client.user.id) {
                    try {
                        await msg.delete();
                        console.log('Mensagem excluída com sucesso!');
                    } catch (deleteError) {
                        console.error('Erro ao excluir mensagem:', deleteError);
                    }
                }
            });
        } catch (error) {
            console.error('Erro ao buscar mensagens do bot na DM:', error);
        }
    }

    setInterval(DELETE100, 4000);
});

client.login(SEU_TOKEN_AQUI);
