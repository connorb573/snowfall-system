void drawString (void *font, float x, float y, char *str) {
/* Draws string ’str’ in font ’font’, at world (x,y,0) */
    char *ch;
    glRasterPos3f(x, y, 0.0);
    for (ch= str; *ch; ch++)
        glutBitmapCharacter(font, (int)*ch);
}
