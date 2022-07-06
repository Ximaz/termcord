# Termcord
The main goal of this project is to be able to have some Discord features into a terminal. However it won't be able to do as many thing as a Discord client would allow you to. Using a user token to interact with the API might ban your account. So, it uses the [OAuth2 API](https://discord.com/developers/docs/topics/oauth2#oauth2), which will let you see users, their messages, the channels with the guilds, and so one... You might even be able to connect in voice chat, but not to type-in.

## Resources
- [The Discord OAuth2 API](https://discord.com/developers/docs/topics/oauth2#oauth2)

## TODO
- Include the [`state`](https://discord.com/developers/docs/topics/oauth2#state-and-security) param to OAuth2 URL

## Planned features
Below you will find the list of all feature that can be integrated to the project.
- Lines starting by `// REQUIRES DISCORD APPROVAL` are the feature that wont be added in the project, since Discord has to verify each application to allow or not the usage of those endpoints.
- Lines starting by `// USELESS` are the feature that can't be aded in the project, since it doesn't match for a user-client usage. E.g : the bot feature is worthless.
```c
static char const *OAUTH2_SCOPES[] = {
    "identify",
    "email",
    "connections",
    "guilds",
    "guilds.members.read",
    "gdm.join",
    "applications.builds.read",
    "applications.commands",
    "applications.store.update",
    "applications.entitlements",
    "messages.read",
    // USELESS : "webhook.incoming",
    // USELESS : "bot",
    // REQUIRES DISCORD APPROVAL : "rpc",
    // REQUIRES DISCORD APPROVAL : "rpc.notifications.read",
    // REQUIRES DISCORD APPROVAL : "rpc.voice.read",
    // REQUIRES DISCORD APPROVAL : "rpc.voice.write",
    // REQUIRES DISCORD APPROVAL : "rpc.activities.write",
    // REQUIRES DISCORD APPROVAL : "applications.builds.upload",
    // REQUIRES DISCORD APPROVAL : "activities.read",
    // REQUIRES DISCORD APPROVAL : "activities.write",
    // REQUIRES DISCORD APPROVAL : "relationships.read",
    // REQUIRES DISCORD APPROVAL : "voice",
    // REQUIRES DISCORD APPROVAL : "dm_channels.read",
};
```

## Roadmap
- [X] Generation of OAuth2 url.
- [X] Adding a .env parser.
- [X] Recieve the Discord OAuth2 token (JSON not parsed yet, but API is setted up).
- [ ] Sending web requests to Discord OAuth2 API (token refresh, API interaction, ...) token.
- [ ] Other stuff that I don't have idea for now.
- [ ] Display a good GUI into the terminal.

## Setup
### Dependencies
First of all, you have, for now, one dependency to download if not already done. It's the [libcurl](https://curl.se/libcurl/) library. It will make Termcord to be able to perform web requests. On `debian`-based distro, you can simply type :
```console
sudo apt install libcurl4-openssl-dev -y
```

### Installation
The first thing you have to do is going to [https://discord.com/developers/applications/](https://discord.com/developers/applications/993615435079630848/information) to create a Discord application. Then, go to the `OAuth2` section to get the `client_id` and the `client_secret`. Store them to a .env file like so :
```env
CLIENT_ID=<client_id>
CLIENT_SECRET=<client_secret>
```
