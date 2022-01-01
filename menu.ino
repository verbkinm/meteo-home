void menuSelect(void)
{
    tft.fillRect(0, 195, 320, 5, BLACK);
    tft.fillRect(40 * static_cast<int>(currentPage), 195, 40, 5, TFT_COLOR::YELLOW);
}
