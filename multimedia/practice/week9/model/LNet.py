import torch
import torch.nn as nn
import torch.nn.functional as F

import math

class LeNet(nn.Module):
  def __init__(self, _input_channel, num_class):
    super().__init__()
    self.conv1 = nn.Conv2d(in_channels=_input_channel, out_channels=6, kernel_size = 5, padding = 0)
    self.conv2 = nn.Conv2d(in_channels=6, out_channels=12, kernel_size=5, padding = 0)
    self.conv3 = nn.Conv2d(in_channels=12, out_channels=120, kernel_size=5, padding = 0)

    # 빈 칸 채우기
    self.fc_in_features = 120

    self.fc1 = nn.Linear(in_features=self.fc_in_features, out_features=84)
    self.fc2 = nn.Linear(in_features=84, out_features=num_class)

    self.softmax = nn.Softmax(dim=-1)

  def forward(self, x):
    x = F.relu(self.conv1(x))
    x = F.max_pool2d(x, 2, 2)

    x = F.relu(self.conv2(x))
    x = F.max_pool2d(x, 2, 2)
    x = F.relu(self.conv3(x))
    x = x.view(-1, self.fc_in_features)

    x = self.fc1(x)
    x = self.fc2(x)

    x = self.softmax(x)
    return x