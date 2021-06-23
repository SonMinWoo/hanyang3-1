import torch
import torch.nn as nn

import math

class VGG16(nn.Module):
    def __init__(self, _input_channel, num_class):
      super().__init__()
      self.convs = nn.Sequential(
        nn.Conv2d(in_channels=_input_channel, out_channels=64, kernel_size = 3, padding = 1), #1-1(1)
        nn.BatchNorm2d(64, 64),
        nn.ReLU(inplace=True),
        nn.Conv2d(in_channels=64, out_channels=64, kernel_size = 3, padding = 1),#1-2(2)
        nn.BatchNorm2d(64, 64),
        nn.ReLU(inplace=True),
        nn.MaxPool2d(kernel_size=2, stride=2),

        nn.Conv2d(in_channels=64, out_channels=128, kernel_size=3, padding = 1),#2-1(3)
        nn.BatchNorm2d(128, 128),
        nn.ReLU(inplace=True),
        nn.Conv2d(in_channels=128, out_channels=128, kernel_size=3, padding = 1),#2-2(4)
         nn.BatchNorm2d(128, 128),
        nn.ReLU(inplace=True),
        nn.MaxPool2d(kernel_size=2, stride=2), 

        nn.Conv2d(in_channels=128, out_channels=256, kernel_size=3, padding = 1),#3-1(5)
        nn.BatchNorm2d(256, 256),
        nn.ReLU(inplace=True),
        nn.Conv2d(in_channels=256, out_channels=256, kernel_size=3, padding = 1),#3-2(6)
        nn.BatchNorm2d(256, 256),
        nn.ReLU(inplace=True),
        nn.Conv2d(in_channels=256, out_channels=256, kernel_size=3, padding = 1), #3-3(7)
        nn.BatchNorm2d(256, 256),
        nn.ReLU(inplace=True),
        nn.MaxPool2d(kernel_size=2, stride=2), 

        nn.Conv2d(in_channels=256, out_channels=512, kernel_size=3, padding = 1), #4-1(8)
        nn.BatchNorm2d(512, 512),
        nn.ReLU(inplace=True),
        nn.Conv2d(in_channels=512, out_channels=512, kernel_size=3, padding = 1), #4-2(9)
        nn.BatchNorm2d(512, 512),
        nn.ReLU(inplace=True),
        nn.Conv2d(in_channels=512, out_channels=512, kernel_size=3, padding = 1), #4-3(10)
        nn.BatchNorm2d(512, 512),
        nn.ReLU(inplace=True),
        nn.MaxPool2d(kernel_size=2, stride=2),

        nn.Conv2d(in_channels=512, out_channels=512, kernel_size=3, padding = 1), #5-1(11)
        nn.BatchNorm2d(512, 512),
        nn.ReLU(inplace=True),
        nn.Conv2d(in_channels=512, out_channels=512, kernel_size=3, padding = 1), #5-2(12)
        nn.BatchNorm2d(512, 512),
        nn.ReLU(inplace=True),
        nn.Conv2d(in_channels=512, out_channels=512, kernel_size=3, padding = 1), #5-3(13)
        nn.BatchNorm2d(512, 512),
        nn.ReLU(inplace=True),
        nn.MaxPool2d(kernel_size=2, stride=2),
      )

      self.fc_in_features = 512 * 7 * 7
      self.fcs = nn.Sequential(
        nn.Linear(self.fc_in_features, 4096), #fully-contected 1 (14)
        nn.ReLU(True),
        nn.Dropout(),
        nn.Linear(4096, 4096), #fully-contected 2 (15)
        nn.ReLU(True),
        nn.Dropout(),
        nn.Linear(4096, out_features=num_class), #fully-contected 3 (16)
      )


      self.softmax = nn.Softmax(dim=-1)


    def forward(self, x):
        # forward 구현
        x = self.convs(x)
        x = torch.flatten(x, 1)
        x = self.fcs(x)

        return x