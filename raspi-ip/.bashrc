#!/bin/bash
hostname -I > ip.md

git add ip.md
git commit -m "latest IP"
git push