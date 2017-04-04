Это минимальный http сервер.
Планируется реализовать его используя unix сокеты.
Сервер работает по следующей схеме (Здесь позже будет схема, честно :))

**ServerListening**AcceptConnect**ParsingRequest**ServerListening***********************************
                                                *
                                                *
                                                **CreateCommandFromRequest**AttachCommandToThreadPool
