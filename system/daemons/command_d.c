#ifndef CMD_PATH_WIZ
#define CMD_PATH_WIZ ({"/cmds/wiz/"})
#endif
#ifndef CMD_PATH_STD
#define CMD_PATH_STD ({"/cmds/std/"})
#endif

nosave string *path = CMD_PATH_STD;

private nosave mapping default_aliases = ([
    "s":"go south",
    "n":"go north",
    "w":"go west",
    "e":"go east",
    "sd":"go southdown",
    "nd":"go northdown",
    "wd":"go westdown",
    "ed":"go eastdown",
    "su":"go southup",
    "nu":"go northup",
    "wu":"go westup",
    "eu":"go eastup",
    "sw":"go southwest",
    "se":"go southeast",
    "nw":"go northwest",
    "ne":"go northeast",
    "d":"go down",
    "u":"go up",
    "i":"inventory",
    "l":"look",
]);

string default_alias(string verb)
{
    verb = lower_case(verb);

    if (sscanf(verb, "l %s", verb))
    {
        return "look " + verb;
    }

    return default_aliases[verb];
}

mapping query_default_alias()
{
    return default_aliases;
}

void set_alias(mapping aliases)
{
    default_aliases += aliases;
}

object find_command(string verb)
{
    object file;

    if (wizardp(this_player()))
    {
        path += CMD_PATH_WIZ;
    }

    if (!arrayp(path))
        return 0;

    foreach(string p in path)
    {
        if (file = load_object(p + verb))
        {
            return file;
        }
    }

    return 0;
}