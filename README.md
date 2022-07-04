# Termcord
The main goal of this project is to be able to have some Discord features into a terminal. However it won't be able to do as many thing as a Discord client would allow you to. Using a user token to interact with the API might ban your account. So, it uses the [OAuth2 API](https://discord.com/developers/docs/topics/oauth2#oauth2), which will let you see users, their messages, the channels with the guilds, and so one... You might even be able to connect in voice chat, but not to type-in.

# Resources
- [The Discord OAuth2 API](https://discord.com/developers/docs/topics/oauth2#oauth2)

# TODO
- Include the [`state`](https://discord.com/developers/docs/topics/oauth2#state-and-security) param to OAuth2 URL

# Roadmap
- [X] Generation of OAuth2 url
- [ ] Recieve the Discord OAuth2 token.
- [ ] Sending web requests to Discord OAuth2 API (token refresh, API interaction, ...) token.
- [ ] Other stuff that I don't have idea for now.
- [ ] Display a good GUI into the terminal.

# Setup
The first thing you have to do is going to [https://discord.com/developers/applications/](https://discord.com/developers/applications/993615435079630848/information) to create a Discord application. Then, go to the `OAuth2` section to get the `client_id` and the `client_secret`. Store them to a .env file like so :
```env
CLIENT_ID=<client_id>
CLIENT_SECRET=<client_secret>
```
