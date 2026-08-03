@echo off
cd C:\Aemulus\techFlow3\Projects\VSProjects\SampleProfile\OX03A10EY1E_FT3_60C_aCSP_RF0101\OX03A10EY1E_FT3_60C_aCSP_RF0101\RTPlotter\
@echo off
taskkill /IM RTPlot.exe /F
timeout 3
taskkill /IM gnuplot.exe /F

