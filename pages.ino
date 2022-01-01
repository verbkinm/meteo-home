void pageSelect(void)
{
    clearPage();
    switch(currentPage)
    {
    case PAGE::HOME:
        page_0_Draw();
        break;
    case PAGE::SETTING:
        page_1_Draw();
        break;
    case PAGE::CALENDAR:
        page_2_Draw();
        break;
    case PAGE::ALARM:
        page_3_Draw();
        break;
    case PAGE::DIAGRAM:
        page_4_Draw();
        break;
    case PAGE::WIFI:
        page_5_Draw();
        break;
    }

    draw_statusPanel();
}

void clearPage()
{
    tft.fillRect(0, 0, 250, 17, TFT_COLOR::BLACK);
    tft.fillRect(0, 17, 320, 178, TFT_COLOR::BLACK);
}
