{
  "targets": [
    {
      "target_name": "vercmp",
      "sources": [
        "vercmp.cc",
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}