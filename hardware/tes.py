temp = float
daily_lying = float
footstep = integer
estrus = Boolean
silent_heat = Boolean

if 38.27 <= temp <= 38.53 and footstep > 1200 and daily_lying < 29.83:
    estrus = True

elif 38.27 <= temp <= 38.53 and footstep != 1200 and daily_lying != 29.83:
    silent_heat = True

else:
    estrus = False

    