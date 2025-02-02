void exit_on_fail(short result)
{
    if (result < 0)
    {
        exit(result);
    }

    return result;
}
