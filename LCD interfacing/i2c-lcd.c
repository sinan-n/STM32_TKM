#include "i2c-lcd.h"
#include "string.h"

extern I2C_HandleTypeDef hi2c1;     // ensure hi2c1 is the same instance from CubeMX

#define LCD_I2C_ADDR 0x4E   // try 0x4E (0x27<<1); if not working try 0x7E
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_RS        0x01

static void lcd_write_nibble(uint8_t nibble, uint8_t mode)
{
    uint8_t data[2];

    data[0] = (nibble & 0xF0) | mode | LCD_BACKLIGHT | LCD_ENABLE;
    data[1] = (nibble & 0xF0) | mode | LCD_BACKLIGHT;
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, data, 2, HAL_MAX_DELAY);
    HAL_Delay(1);
}

void lcd_send_cmd(char cmd)
{
    lcd_write_nibble(cmd & 0xF0, 0);
    lcd_write_nibble((cmd << 4) & 0xF0, 0);
}

void lcd_send_data(char data)
{
    lcd_write_nibble(data & 0xF0, LCD_RS);
    lcd_write_nibble((data << 4) & 0xF0, LCD_RS);
}

void lcd_init(void)
{
    HAL_Delay(50);
    // Initialization sequence for 4-bit mode
    lcd_write_nibble(0x30, 0); HAL_Delay(5);
    lcd_write_nibble(0x30, 0); HAL_Delay(1);
    lcd_write_nibble(0x30, 0); HAL_Delay(1);
    lcd_write_nibble(0x20, 0); HAL_Delay(1); // Set 4-bit mode

    lcd_send_cmd(0x28); // 4-bit, 2 line, 5x8 dots
    lcd_send_cmd(0x08); // display off
    lcd_clear();
    lcd_send_cmd(0x06); // entry mode
    lcd_send_cmd(0x0C); // display on, cursor off
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}

void lcd_put_cur(int row, int col)
{
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(addr);
}

void lcd_send_string(char *str)
{
    while(*str) lcd_send_data(*str++);
}
