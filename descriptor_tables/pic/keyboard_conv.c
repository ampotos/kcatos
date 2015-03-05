/*
** keyboard_conv.c for KCatos in /home/ampotos/kcatos
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Mon Mar  2 17:02:02 2015 
** Last update Thu Mar  5 09:58:00 2015 
*/

#include <utils/types.h>
#include <descriptor_tables/pic/keyboard.h>
#include <utils/string.h>

static const char	special_key_tab[6] = {
  56, // alt and alt_gr with 96 before
  29, // ctrl_l or ctr_r with 96 before
  54, // maj_r
  42, // maj_l
  58, // maj_lock
  69, // ver_num
};

static const char       convert_table[94] =
  {0, // nothing scancode start to 1
   0, //echap
   '1','2','3','4','5','6','7','8','9','0','o','+',
   0, // del
   '\t',
   'a','z','e','r','t','y','u','i','o','p','^','$',
   '\n', // also enter form keypad with 96 before
   0, //ctrl_g and ctr_l with 96 before
   'q','s','d','f','g','h','j','k','l','m',
   'u', // realy is ù
   0, //²
   0, //maj_l
   '*',
   'w','x','c','v','b','n',',', ';',
   ':', // also '/' from numpad with 96 before
   '!',
   0, // maj_r
   '*', // numpad
   0, 
   ' ',
   0, // maj lock
   0/*f1*/,0/*f2*/,0/*f3*/,0/*f4*/,0/*f5*/,0/*f6*/,0/*f7*/,0/*f8*/,0/*f9*/,0/*f10*/,
   0, // ver num
   0, // unknow 70 (maybe fn)
   '7', // keypad also impr ecr with 96 before
   '8', // keypad also arrow up with 96 before
   '9', // keypad
   '-', // keypad
   '4', // keypad also arrow left with 96 before
   '5', // keypad
   '6', // keypad aslo arrow right with 96 before
   '+', // keypad
   '1', // keypad
   '2', // keypad also arrow down with 96 before
   '3', // keypad
   '0', // also insert with 96 before
   '.', //keypad  also supr with 96 before
   0, // unknown 84
   0, //unknow 85
   '<',
   0, // f11
   0, // f12
   0, // unknown 89
   0, // unknown 90
   0, // super
   0, // unkown 92
   0}; // click key with 96 before

u32	is_special_k(u8 scancode)
{
  int	ct = -1;

  while (ct < 6 && scancode != special_key_tab[++ct]);
  if (ct == 6)
    return (0);
  return (1);
}

u32	get_flag_special(u8 code, u32 state)
{
  if (code == 96)
    return (FUCKING_96);

  if (code == 56)
    return ((state & FUCKING_96) ? ALT_GR_KMASK : ALT_L_KMASK);

  if (code == 29)
    return ((state & FUCKING_96) ? CTRL_R_KMASK : CTRL_L_KMASK);

  if (code == 54)
    return (MAJ_R_KMASK);

  if (code == 42)
    return (MAJ_L_KMASK);      

  if (code == 58)
    return (MAJ_LOCK_KMASK);

  // it's 69
  return (VER_NUM_KMASK);
}

u8	alt_conv(u8 c)
{
  if (c == '1')
    return (' ');
  if (c == '2')
    return ('~');
  if (c == '3')
    return ('#');
  if (c == '4')
    return ('{');
  if (c == '5')
    return ('[');
  if (c == '6')
    return ('|');
  if (c == '7')
    return ('`');
  if (c == '8')
    return ('\\');
  if (c == '9')
    return ('^');
  if (c == '0')
    return ('@');
  if (c == 'o')
    return (']');
  if (c == '+')
    return ('}');
  return (' ');
}

u8	normal_conv(u8 c)
{
  if (c == '1')
    return ('&');
  if (c == '2')
    return ('e');
  if (c == '3')
    return ('"');
  if (c == '4')
    return ('\'');
  if (c == '5')
    return ('(');
  if (c == '6')
    return ('-');
  if (c == '7')
    return ('e');
  if (c == '8')
    return ('_');
  if (c == '9')
    return ('c');
  if (c == '0')
    return ('a');
  if (c == 'o')
    return (')');
  if (c == '+')
    return ('=');
  return (' ');  
}

u8	maj_conv(u8 c)
{
  if (c == '<')
    return ('>');
  if (c == ',')
    return ('?');
  if (c == ';')
    return ('.');
  if (c == ':')
    return ('/');
  if (c == 'u')
    return ('%');
  return (' ');
}

u8	get_real_char(u8 c, u32 state)
{
  if ((c >= 2 && c <= 13)) // num not from numpad
    {
      if ( ((!(state & MAJ_LOCK_ACTIVE) && (state & (MAJ_L_KMASK | MAJ_R_KMASK))) // si pas maj_lock but one or two maj key are pressed
	   || ((state & MAJ_LOCK_ACTIVE) && !(state & (MAJ_L_KMASK | MAJ_R_KMASK))))
      	  && !(state & ALT_GR_KMASK) && !(state & ALT_L_KMASK)) // if only maj key pressed (without maj_lock)
	return (convert_table[c]);
      if ((state & ALT_GR_KMASK) || (state & ALT_L_KMASK)) // if alt keys are pressed
	return (alt_conv(convert_table[c]));
      return (normal_conv(convert_table[c]));
    }
  if ((c == 40 || c == 86 || (c >= 50 && c <= 52))
      && (state & (MAJ_L_KMASK | MAJ_R_KMASK)))
    return (maj_conv(convert_table[c]));
  if (is_alpha_c(convert_table[c]) && // si c'est un e lettre de l'alphabet et que maj activer on met en maj
      ((!(state & MAJ_LOCK_ACTIVE) && (state & (MAJ_L_KMASK | MAJ_R_KMASK))) // si pas maj_lock but one or two maj key are pressed
       || ((state & MAJ_LOCK_ACTIVE) && !(state & (MAJ_L_KMASK | MAJ_R_KMASK))))
       && !(state & ALT_GR_KMASK) && !(state & ALT_L_KMASK))
    return (convert_table[c] - ('a' - 'A'));
  return (convert_table[c]);
}

static u32	keyboard_state; // state of special key

u32    keyboard_ascii_convert(char *buff, u32 size, u32 change_state)
{
  u32	tmp_state = keyboard_state;
  u32	ct_orig = 0, ct_trad = 0;
  u32	available_raw = keyboard_available_raw();
  
  if (!available_raw)
    return (0);
  while (ct_trad < size && ct_orig < available_raw)
    {
      if (!(g_keyboard.buff[ct_orig] & 0x80) && !is_special_k(g_keyboard.buff[ct_orig]))// key release
	{
	  if (g_keyboard.buff[ct_orig] == 96)
	    ++ct_orig;
	  else if (convert_table[g_keyboard.buff[ct_orig]])
	    buff[ct_trad++] = get_real_char(g_keyboard.buff[ct_orig++], tmp_state);
	  else
	    ct_orig++;
	}
     else 
	{
	  if ((g_keyboard.buff[ct_orig] & 0x80) && is_special_k(g_keyboard.buff[ct_orig] ^ 0x80)) // if special key press
	    tmp_state |= get_flag_special(g_keyboard.buff[ct_orig] ^ 0x80, tmp_state);
	  else if (!(g_keyboard.buff[ct_orig] & 0x80) && is_special_k(g_keyboard.buff[ct_orig])) // special key release
	    {
	      u32	flag = get_flag_special(g_keyboard.buff[ct_orig], tmp_state);
	      if (flag == MAJ_LOCK_KMASK)
		tmp_state ^= MAJ_LOCK_ACTIVE;
	      else if (flag == VER_NUM_KMASK)
		tmp_state ^= MAJ_LOCK_ACTIVE;
	      tmp_state ^= flag;
	    }
	  
	  if (g_keyboard.buff[ct_orig - 1] != 96 && (tmp_state & FUCKING_96)) // 96 is usefull only for the next scancode
	    tmp_state ^= FUCKING_96;
	  ct_orig++;
	}      
    }
  if (change_state)
    keyboard_state = tmp_state;

  return (ct_orig);
}
