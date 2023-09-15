int main(void)
{
    RVS_Init();
    for (int i = 0; i < 1000000; i++)
    {
        RVS_Ipoint(i);
    }
    RVS_Output();
}