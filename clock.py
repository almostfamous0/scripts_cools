import tkinter as tk
from tkinter import PhotoImage
import os
from time import strftime

root = tk.Tk()
root.title('Seu relógio')
root.geometry("600x320")
root.maxsize(600, 320)
root.minsize(600, 328)
root.configure(background="#1d1d1d")

tela = tk.Canvas(root, width=600, height=20, bg='#1d1d1d', bd=0, highlightthickness=0, relief='ridge')
tela.pack()

saudacao = tk.Label(root, bg='#1d1d1d', fg='#8e27ea', font=("Montserrat", 16))
saudacao.pack()

data = tk.Label(root, bg="#1d1d1d", fg='#8e27ea', font=('Montserrat', 14))
data.pack(pady=2)

horas = tk.Label(root, bg='#1d1d1d', fg='#8e27ea', font=('Montserrat', 64, 'bold'))
horas.pack(pady=2)

def toggle_dark_mode():
    if root['bg'] == '#1d1d1d':
        root['bg'] = 'white'
        tela['bg'] = 'white'
        saudacao['bg'] = 'white'
        data['bg'] = 'white'
        horas['bg'] = 'white'
    else:
        root['bg'] = '#1d1d1d'
        tela['bg'] = '#1d1d1d'
        saudacao['bg'] = '#1d1d1d'
        data['bg'] = '#1d1d1d'
        horas['bg'] = '#1d1d1d'

dark_mode_button = tk.Button(root, command=toggle_dark_mode)
dark_mode_button.config(image=None, bd=0, bg='#1d1d1d')
dark_mode_button.pack(pady=10)

def get_saudacao():
    nome_usuario = 'NOBODY_KNOWS'
    saudacao.config(text=f'Olá, {nome_usuario}')

def get_data():
    data_atual = strftime('%s, %d %b %Y')
    data.config(text=data_atual)

def get_horas():
    hora_atual = strftime('%H:%M:%S')
    horas.config(text=hora_atual)
    horas.after(1080, get_horas)

get_saudacao()
get_data()
get_horas()

root.mainloop()

