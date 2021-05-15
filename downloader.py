#!/usr/bin/env python3
import sys
import torch
import timm

def download(name):
    model = timm.create_model(name, pretrained=False, num_classes=10)
    serialized_model = torch.jit.script(model)
    serialized_model.save(f'{name}.pt')

if __name__ == '__main__':
    swins = [it for it in timm.list_models(pretrained=True) if it.find('swin') != -1]
    for id in range(len(swins)):
        print(f'[{id}]: {swins[id]}')
    input_id = input('Input the \"id\" of the model: ')
    if 0 <= int(input_id) < len(swins):
        download(swins[int(input_id)])
    else:
        print("Invalid number")
