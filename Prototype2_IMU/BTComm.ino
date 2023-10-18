void btRead()
{
  if (btserial.available())
    btIN = btserial.read();

  if (btserial.read() == A)
  {
    signalAOK();
  }
